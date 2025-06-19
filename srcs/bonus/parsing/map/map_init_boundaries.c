#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "map_types.h"
#include "parsing.h"

void	get_map_dimensions(t_infos *infos, int map_start, \
													int *height, int *width)
{
	int	i;
	int	max_width;

	*height = 0;
	max_width = 0;
	i = map_start;
	while (infos->data->lines[i])
	{
		if (ft_strlen(infos->data->lines[i]) > (size_t)max_width)
			max_width = ft_strlen(infos->data->lines[i]);
		(*height)++;
		i++;
	}
	*width = max_width;
}

char	**init_extended_map(t_ext_map *ext_map)
{
	char	**extended_map;

	extended_map = malloc(sizeof(char *) * (ext_map->height + 3));
	if (extended_map == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		return (NULL);
	}
	extended_map[0] = malloc(sizeof(char) * (ext_map->width + 3));
	if (extended_map[0] == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		free(extended_map);
		return (NULL);
	}
	ft_memset(extended_map[0], ' ', ext_map->width + 2);
	extended_map[0][ext_map->width + 2] = '\0';
	return (extended_map);
}

bool	init_map_borders(char **map_ext, t_ext_map *ext_map)
{
	int	i;

	i = 0;
	while (++i <= ext_map->height)
	{
		map_ext[i] = malloc(sizeof(char) * (ext_map->width + 3));
		if (map_ext[i] == NULL)
		{
			ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
			free_extended_map(map_ext, i);
			return (false);
		}
	}
	map_ext[ext_map->height + 1] = malloc(sizeof(char) * (ext_map->width + 3));
	if (map_ext[ext_map->height + 1] == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		free_extended_map(map_ext, ext_map->height + 1);
		return (false);
	}
	ft_memset(map_ext[ext_map->height + 1], ' ', ext_map->width + 2);
	map_ext[ext_map->height + 1][ext_map->width + 2] = '\0';
	map_ext[ext_map->height + 2] = NULL;
	return (true);
}
