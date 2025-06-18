#include "common.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "sound_internal.h"
#include "sound.h"
#include "stdbool.h"
#include "structs_b.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static bool	check_cards_for_bluetooth(void)
{
	int		pipefd[2];
	pid_t	pid;
	char	buffer[256];
	ssize_t	bytes_read;
	int		status;

	pid = create_child_process(pipefd);
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		setup_child_process(pipefd);
		execl("/bin/sh", "sh", "-c", PACTL_BLUETOOTH_GREP, (char *) NULL);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		return (ft_strlen(buffer) > 0);
	}
	return (false);
}

bool	check_bluetooth_audio_connected(void)
{
	bool	bluetooth_found;

	bluetooth_found = execute_pactl_command(PACTL_BLUEZ_GREP);
	if (!bluetooth_found)
		bluetooth_found = check_cards_for_bluetooth();
	if (bluetooth_found)
		ft_dprintf(2, GREEN DEVICE_CONNECTED RESET);
	else
		ft_dprintf(2, RED NO_DEVICE_CONNECTED RESET);
	return (bluetooth_found);
}
