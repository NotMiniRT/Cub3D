#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"
#include "sound.h"

static void	str_to_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
}

static bool	check_bluetooth_keywords(char *buffer)
{
	str_to_lowercase(buffer);
	if (ft_strnstr(buffer, BLUETOOTH, ft_strlen(BLUETOOTH)))
		return (true);
	if (ft_strnstr(buffer, BLUEZ, ft_strlen(BLUEZ)))
		return (true);
	if (ft_strnstr(buffer, BT, ft_strlen(BT)))
		return (true);
	if (ft_strnstr(buffer, A2DP, ft_strlen(A2DP)))
		return (true);
	if (ft_strnstr(buffer, HEADSET, ft_strlen(HEADSET)))
		return (true);
	return (false);
}

static bool	read_and_check_output(int fd)
{
	char	buffer[256];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (check_bluetooth_keywords(buffer))
			return (true);
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	}
	return (false);
}

bool	execute_pactl_command(const char *cmd)
{
	int		pipefd[2];
	pid_t	pid;
	bool	found;
	int		status;

	pid = create_child_process(pipefd);
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		setup_child_process(pipefd);
		execl("/bin/sh", "sh", "-c", cmd, (char *) NULL);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	found = read_and_check_output(pipefd[0]);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	return (found);
}
