#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static int	handle_remaining_buffer(char **buffer, char *line, size_t i)
{
	char	*temp;

	if (!(*buffer)[i])
	{
		free(*buffer);
		*buffer = NULL;
		return (1);
	}
	temp = ft_strdup(&(*buffer)[i]);
	if (temp == NULL)
	{
		free(line);
		free(*buffer);
		*buffer = NULL;
		return (0);
	}
	free(*buffer);
	*buffer = temp;
	return (1);
}

static char	*extract_line(char **buffer)
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
	if (handle_remaining_buffer(buffer, line, i) == 0)
		return (NULL);
	return (line);
}

static char	*join_and_free(char *s1, char *s2) // j'ai pas trouvé d'autres solutions a call ft_strlen 2 fois par variable ici. On depasse les 25 lignes sinon
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

int	read_line_check(int fd, char *buffer)
{
	if (fd == CLEAR_BUFFER)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (-1);
	}
	if (fd < 0)
		return (-1);
	return (0);
}

static char	*read_line_main_loop(ssize_t bytes_read, char *buffer, \
	char *read_buffer, int fd)
{
	while (bytes_read > 0 && (!buffer || (!ft_strchr(buffer, '\n') && buffer[0] != '\0')))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
			if (buffer)
				free(buffer);
			free(read_buffer);
			buffer = NULL;
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		buffer = join_and_free(buffer, read_buffer);
		if (buffer == NULL)
		{
			free(read_buffer);
			return (NULL);
		}
	}
	return (buffer);
}

char	*read_line(int fd)
{
	static char	*buffer = NULL;
	char		*read_buffer;
	char		*line;
	ssize_t		bytes_read;

	if (read_line_check(fd, buffer) == -1)
		return (NULL);
	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_buffer == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		return (NULL);
	}
	bytes_read = 1;
	buffer = read_line_main_loop(bytes_read, buffer, read_buffer, fd);
	// if (buffer == NULL)
	// while (bytes_read > 0 && (!buffer || (!ft_strchr(buffer, '\n') && buffer[0] != '\0')))
	// {
	// 	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	// 	if (bytes_read == -1)
	// 	{
	// 		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
	// 		if (buffer)
	// 			free(buffer);
	// 		free(read_buffer);
	// 		buffer = NULL;
	// 		return (NULL);
	// 	}
	// 	read_buffer[bytes_read] = '\0';
	// 	if (bytes_read == 0)
	// 		break ;
	// 	buffer = join_and_free(buffer, read_buffer);
	// 	if (buffer == NULL)
	// 	{
	// 		free(read_buffer);
	// 		return (NULL);
	// 	}
	// }
	free(read_buffer);
	line = extract_line(&buffer);
	return (line);
}



char	**read_all_lines(t_parsing *data)
{
	data->line = read_line(data->fd);
	while (data->line)
	{
		printf("%s", data->line); // Debug pour l'instant
		if (data->count >= data->capacity - 1)
		{
			data->capacity *= 2;
			data->new_lines = malloc(sizeof(char *) * data->capacity);
			if (data->new_lines == NULL)
				return (clear_read_lines(data));
			ft_memcpy(data->new_lines, data->lines,
				data->count * sizeof(char *));
			free(data->lines);
			data->lines = data->new_lines;
			data->new_lines = NULL;
		}
		data->lines[data->count++] = data->line;
		data->line = read_line(data->fd);
		if (data->line == NULL)
			break ;
	}
	data->lines[data->count] = NULL;
	return (data->lines);
}
