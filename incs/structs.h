#ifndef STRUCTS_H
# define STRUCTS_H

# include "stdlib.h"

typedef enum moves
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3,
	TRIGHT = 4,
	TLEFT = 5,
	SHIFT = 6
}	t_moves;

typedef struct s_player
{
	double	x;
	double	y;
	double	fov_angle;
}	t_player;

typedef struct s_image_cub
{
	void	*sprite;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
}	t_image_cub;

typedef struct s_main_struct
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		*player;
	t_image_cub		*frame;
	t_image_cub		*wall_n;
	t_image_cub		*wall_o;
	t_image_cub		*wall_s;
	t_image_cub		*wall_e;
	t_image_cub		*fog;
	int				ground;
	int				ceil;
	char			**map;
	double			*r_h_tab;
	double			*cos_r_h_tab;
	size_t			created_at;
	size_t			last_move;
	short int		inputs[7];
	int				is_moving;
}	t_main_struct;

typedef struct s_render_calculus
{
	double	res[4];
	double	height;
	int		text_x;
	int		text_y;
	double	step;
	double	text_y_index;
	int		height_check_minus;
	int		height_check_plus;
	double	wall_pc;
	double	teta;
	int		*line_add;
}	t_render_calculus;

typedef struct s_ray_calculus
{
	double	dir_x;
	double	dir_y;
	double	player_x;
	double	player_y;
	double	tilde_step_x;
	double	tilde_step_y;
	double	dist_x;
	double	dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		map_x;
	int		map_y;
	double	wall_x;
	double	wall_y;
	double	dist;
	int		flag_dist;
}	t_ray_calculus;

#endif
