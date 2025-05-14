#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static void	free_color(t_color *color)
{
	if (color == NULL)
		return ;
	if (color->line)
		free(color->line);
	free(color);
}

void	free_scene(t_scene *scene)
{
	if (scene == NULL)
		return ;
	free_color(scene->floor_color);
	free_color(scene->ceiling_color);
	if (scene->we_texture)
		free(scene->we_texture);
	if (scene->so_texture)
		free(scene->so_texture);
	if (scene->no_texture)
		free(scene->no_texture);
	if (scene->ea_texture)
		free(scene->ea_texture);
	free(scene);
	scene = NULL;
}

void	cleanup_parsing(t_infos *infos)
{
	if (infos == NULL || infos->data == NULL)
		return ;
	if (infos->scene != NULL)
		free_scene(infos->scene);
	read_line(CLEAR_BUFFER);
	if (infos->data->fd != -1)
		close(infos->data->fd);
	if (infos->data->lines != NULL)
	{
		if (infos->data->count > 0)
			free_array(infos->data->lines);
		else
			free(infos->data->lines);
		infos->data->lines = NULL;
	}
	if (infos->data->line != NULL)
	{
		free(infos->data->line);
		infos->data->line = NULL;
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

void	free_extended_map(char **extended_map, int height)
{
	int	i;

	if (!extended_map)
		return ;
	i = 0;
	while (i <= height)
	{
		if (extended_map[i])
			free(extended_map[i]);
		i++;
	}
	free(extended_map);
}
