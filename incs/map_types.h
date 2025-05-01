#ifndef MAP_TYPES_H
# define MAP_TYPES_H

/*
** Structure pour représenter les coordonnées sur la carte
*/
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/*
** Structure contenant les informations de la carte
*/
typedef struct s_map_data
{
	char	**map;
	int		height;
	int		width;
}	t_map_data;

/*
** Structure pour la création de la carte étendue
*/
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
