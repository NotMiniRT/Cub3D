#ifndef MAP_PROCESSING_H
# define MAP_PROCESSING_H

# include <stdbool.h>

typedef struct s_infos		t_infos;
typedef struct s_map_data	t_map_data;
typedef struct s_ext_map	t_ext_map;

void	get_map_dimensions(t_infos *infos, int map_start,
			int *height, int *width);

void	mark_spaces_as_exterior(t_map_data map_data);

char	**create_extended_map(t_infos *infos, t_ext_map *ext_map);
char	**init_extended_map(t_ext_map *ext_map);

bool	init_map_borders(char **map_ext, t_ext_map *ext_map);

#endif
