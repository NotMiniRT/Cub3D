#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

void	init_data(t_parsing *data, char **av);
void	cleanup_parsing(t_parsing *data);

/**
 * @brief Extracts a line from the buffer
 *
 * @param buffer Current buffer
 * @return char* Extracted line
 */
static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	i;

	if (!*buffer || !**buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *buffer, i);
	line[i] = '\0';
	if ((*buffer)[i])
	{
		temp = ft_strdup(&(*buffer)[i]);
		free(*buffer);
		*buffer = temp;
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	j = -1;
	while (++j < len2)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	free(s1);
	return (result);
}

/**
 * @brief Reads a line from a file descriptor
 *
 * @param fd File descriptor
 * @return char* Line read from fd
 */
char	*read_line(int fd)
{
	static char	*buffer = NULL;
	char		*read_buffer;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0)
		return (NULL);
	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!buffer || !ft_strchr(buffer, '\n')))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break;
		buffer = join_and_free(buffer, read_buffer);
		if (buffer == NULL)
		{
			free(read_buffer);
			return (NULL);
		}
	}
	free(read_buffer);
	line = extract_line(&buffer);
	return (line);
}

/**
 * @brief Reads all lines from a file into an array of strings
 *
 * @param fd File descriptor
 * @return char** Array of strings (NULL-terminated)
 */
char	**read_all_lines(char **av)
{
	t_parsing	data;

	init_data(&data, av);
	data.line = read_line(data.fd);
	while (data.line)
	{
		printf("%s", data.line); // debug
		if (data.count >= data.capacity - 1)
		{
			data.capacity *= 2;
			data.new_lines = malloc(sizeof(char *) * data.capacity);
			if (data.new_lines == NULL)
			{
				while (data.count--)
					free(data.lines[data.count]);
				free(data.lines);
				free(data.line);
				close(data.fd);
				return (NULL);
			}
			ft_memcpy(data.new_lines, data.lines, data.count * sizeof(char *));
			free(data.lines);
			data.lines = data.new_lines;
		}
		data.lines[data.count++] = data.line;
		data.line = read_line(data.fd);
	}
	data.lines[data.count] = NULL;
	cleanup_parsing(&data);
	return (data.lines);
}

void	free_lines(char **lines)
{
	size_t	i;

	if (lines == NULL)
		return ;
	i = 0;
	while (lines[i] != NULL)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	lines = NULL;
}

void	cleanup_parsing(t_parsing *data)
{
	if (data->fd != -1)
		close(data->fd);
	if (data->lines != NULL)
		free_lines(data->lines);
	if (data->line != NULL)
		free(data->line);
}

void	init_data(t_parsing *data, char **av)
{
	data->line = NULL;
	data->fd = open(av[1], O_RDONLY); // protect ? ca a deja ete check plus tot
	data->lines = malloc(sizeof(char *) * 16);
	if (data->lines == NULL || data->fd == -1)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		cleanup_parsing(data);
		exit(errno);
	}
	data->count = 0;
	data->capacity = 16;
	data->new_lines = NULL;
}
