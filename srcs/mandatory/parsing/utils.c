#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "parsing.h"
#include "libft.h"
#include "ft_dprintf.h"

void	free_lines(char **lines)
{
	size_t	i;

	if (lines == NULL)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	cleanup_parsing(t_infos *infos)
{
	if (infos == NULL || infos->data == NULL)
		return ;
	read_line(CLEAR_BUFFER);
	if (infos->data->fd != -1)
		close(infos->data->fd);
	if (infos->data->lines != NULL)
	{
		if (infos->data->count > 0)
			free_lines(infos->data->lines);
		else
			free(infos->data->lines);
		infos->data->lines = NULL;
	}
	if (infos->data->line != NULL)
	{
		free(infos->data->line);
		infos->data->line = NULL;
	}
	if (infos->scene != NULL)
	{
		free(infos->scene);
		infos->scene = NULL;
	}
	free(infos->data);
	infos->data = NULL;
}

char	**clear_read_lines(t_parsing *data)
{
	ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
	while (data->count--)
		free(data->lines[data->count]);
	free(data->lines);
	free(data->line);
	close(data->fd);
	return (NULL);
}
