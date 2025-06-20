/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:28 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:44:29 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static char	*read_line_main_loop(ssize_t bytes_read, char *buffer, \
	char *read_buffer, int fd)
{
	while (bytes_read > 0 && \
			(!buffer || (!ft_strchr(buffer, '\n') && buffer[0] != '\0')))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
			if (buffer)
				free(buffer);
			buffer = NULL;
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		buffer = join_and_free(buffer, read_buffer);
		if (buffer == NULL)
			return (NULL);
	}
	return (buffer);
}

char	*read_line(int fd)
{
	static char	*buffer = NULL;
	char		*read_buffer;
	char		*line;
	ssize_t		bytes_read;

	if (!read_line_check(fd, buffer))
		return (NULL);
	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_buffer == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		return (NULL);
	}
	bytes_read = 1;
	buffer = read_line_main_loop(bytes_read, buffer, read_buffer, fd);
	free(read_buffer);
	line = extract_line(&buffer);
	return (line);
}

static char	**is_full_capacity(t_parsing *data)
{
	if (data->count >= data->capacity - 1)
	{
		data->capacity *= 2;
		data->new_lines = ft_calloc(data->capacity, sizeof(char *));
		if (data->new_lines == NULL)
			return (clear_read_lines(data));
		ft_memcpy(data->new_lines, data->lines,
			data->count * sizeof(char *));
		free(data->lines);
		data->lines = data->new_lines;
		data->new_lines = NULL;
	}
	return (data->lines);
}

char	**read_all_lines(t_parsing *data)
{
	data->line = read_line(data->fd);
	if (data->line == NULL)
	{
		if (errno == 0)
			ft_dprintf(STDERR_FILENO, ERR_EMPTY_FILE);
		free_array(data->lines);
		return (NULL);
	}
	while (data->line)
	{
		if (!is_full_capacity(data))
			return (NULL);
		data->lines[data->count++] = data->line;
		data->line = read_line(data->fd);
		if (data->line == NULL && errno != 0)
		{
			free_array(data->lines);
			return (NULL);
		}
		else if (data->line == NULL)
			break ;
	}
	data->lines[data->count] = NULL;
	return (data->lines);
}
