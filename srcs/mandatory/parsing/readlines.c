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
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, *buffer, i);
	line[i] = '\0';
	if ((*buffer)[i])
	{
		temp = ft_strdup(&(*buffer)[i]);
		if (temp == NULL)
		{
			free(line);
			free(*buffer);
			return (NULL);
		}
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

	if (s1 == NULL)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (result == NULL)
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
	while (bytes_read > 0 && (!buffer || (!ft_strchr(buffer, '\n') || !ft_strchr(buffer, '\0')))) // un autre moyen de check si on est en fin de fichier ?
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (buffer)
				free(buffer);
			free(read_buffer);
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
	free(read_buffer);
	line = extract_line(&buffer);
	if (line == NULL)
	{
		free(buffer);
		free(line);
		line = NULL;
	}
	return (line);
}

char	**read_all_lines(t_infos *infos)
{
	infos->data->line = read_line(infos->data->fd);
	while (infos->data->line)
	{
		printf("%s", infos->data->line); // debug pour l'instant
		if (infos->data->count >= infos->data->capacity - 1)
		{
			infos->data->capacity *= 2;
			infos->data->new_lines = malloc(sizeof(char *) * infos->data->capacity);
			if (infos->data->new_lines == NULL)
			{
				while (infos->data->count--)
					free(infos->data->lines[infos->data->count]);
				free(infos->data->lines);
				free(infos->data->line);
				close(infos->data->fd);
				return (NULL);
			}
			ft_memcpy(infos->data->new_lines, infos->data->lines, infos->data->count * sizeof(char *));
			free(infos->data->lines);
			infos->data->lines = infos->data->new_lines;
		}
		infos->data->lines[infos->data->count++] = infos->data->line;
		infos->data->line = read_line(infos->data->fd); // NULL proteger ici ? Si line === NULL c'est que c'est dans read_line que ca a peter, et donc tout a ete free en amont deja. Je sais pas si c'est necessaire de proteger ce retour
		if (infos->data->line == NULL)
		{
			free(infos->data->line); // ce free est en trop a mon avis, ca a deje ete free a l'interieur
			break ; // pour moi il suffit de break la loop et partir. Pour l'instant il manque un indicateur que quelque chose s'est mal passe (soit un exit, soit une valeur de retour d'erreur)
		}
	}
	infos->data->lines[infos->data->count] = NULL;
	cleanup_parsing(infos);
	return (infos->data->lines);
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
		lines[i] = NULL;
		i++;
	}
	free(lines);
	lines = NULL;
}

void	cleanup_parsing(t_infos *infos)
{
	if (infos->data->fd != -1)
		close(infos->data->fd);
	if (infos->data->lines)
	{
		if (infos->data->count > 0)
			free_lines(infos->data->lines);
		else
			free(infos->data->lines);
	}
	if (infos->data->line)
		free(infos->data->line);
	if (infos->scene)
		free(infos->scene);
}

void	init_data(t_infos *infos, char **av)
{
	infos->data->line = NULL;
	infos->data->fd = open(av[1], O_RDONLY);
	infos->data->lines = malloc(sizeof(char *) * 16);
	if (infos->data->lines == NULL || infos->data->fd == -1)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		cleanup_parsing(infos);
		exit(errno);
	}
	infos->data->count = 0;
	infos->data->capacity = 16; // 16 - 1 ?
	infos->data->new_lines = NULL;
}
