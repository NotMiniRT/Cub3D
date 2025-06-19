#ifndef MAP_TYPES_H
# define MAP_TYPES_H

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map_data
{
	char	**map;
	int		height;
	int		width;
}	t_map_data;

typedef struct s_ext_map
{
	char	**map;
	int		height;
	int		width;
	int		map_start;
}	t_ext_map;

typedef struct s_filling
{
	int		i;
	int		j;
	int		src_len;
	char	c;
}	t_filling;

#endif
