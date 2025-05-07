#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static bool	handle_remaining_buffer(char **buffer, char *line, size_t i)
{
	char	*temp;

	if (!(*buffer)[i])
	{
		free(*buffer);
		*buffer = NULL;
		return (true);
	}
	temp = ft_strdup(&(*buffer)[i]);
	if (temp == NULL)
	{
		free(line);
		free(*buffer);
		*buffer = NULL;
		return (false);
	}
	free(*buffer);
	*buffer = temp;
	return (true);
}

char	*extract_line(char **buffer)
{
	char	*line;
	size_t	i;

	if (!*buffer || !**buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, *buffer, i);
	line[i] = '\0';
	if (!handle_remaining_buffer(buffer, line, i))
		return (NULL);
	return (line);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*result;
	ssize_t	i;
	ssize_t	j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		free(s1);
		return (NULL);
	}
	i = -1;
	while (++i < (ssize_t) ft_strlen(s1))
		result[i] = s1[i];
	j = -1;
	while (++j < (ssize_t) ft_strlen(s2))
		result[i + j] = s2[j];
	result[i + j] = '\0';
	free(s1);
	return (result);
}

bool	read_line_check(int fd, char *buffer)
{
	if (fd == CLEAR_BUFFER)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (false);
	}
	if (fd < 0)
		return (false);
	return (true);
}
