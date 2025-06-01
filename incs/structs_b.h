#ifndef STRUCTS_H
# define STRUCTS_H

# include "stdlib.h"


typedef struct s_thread_manager	t_thread_manager;
typedef struct s_image_cub		t_image_cub;


typedef enum e_moves
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3,
	TRIGHT = 4,
	TLEFT = 5,
	SHIFT = 6
}	t_moves;

typedef enum s_types_object
{
	NOTHING = 0,
	ITEM,
	DOOR
}	t_types_object;

typedef struct s_point
{
    double x;
	double y;
}	t_point;

typedef struct s_object_door
{
	t_point	p1;
	t_point	p2;
	int 	x;
	int		y;
	int		side;
	int		status;
}	t_object_door;

typedef struct s_object_collectible
{
	t_point	p1;
	t_point	p2;
	int 	x;
	int		y;
	int		status;
}	t_object_collectible;

typedef union u_objects
{
	t_object_door			*door;
	t_object_collectible	*item;
} t_objects;

typedef struct s_torch
{
    t_image_cub  *frames[4];
    int          current_frame;
    size_t       last_update;
    size_t       frame_duration;
}	t_torch;

typedef struct s_gauge_color
{
	int	r;
	int	g;
	int	b;
	int	color;
}	t_gauge_color;

typedef struct s_minimap_player
{
	int		i;
	int		j;
	int		center_x;
	int		center_y;
	int		dir_x;
	int		dir_y;
	double	distance;
}	t_minimap_player;

typedef struct s_minimap
{
	double				offset_x;
	double				offset_y;
	double				fractional_x;
	double				fractional_y;
	int					block_size;
	int					player_x;
	int					player_y;
	int					x;
	int					y;
	int					map_x;
	int					map_y;
	int					color;
	char				block_type;
}	t_minimap;

typedef struct s_fuel_bar
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		gauge_x;
	int		gauge_y;
	int		gauge_width;
	int		gauge_height;
	int		color;
}	t_fuel_bar;


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
	int		width;
	int		height;
}	t_image_cub;

typedef struct s_main_struct
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		*player;
	t_torch			*torch;

	t_image_cub		*frame;
	t_image_cub		*minimap;
	t_image_cub		*fuel_bar;
	t_image_cub		*wall_n;
	t_image_cub		*wall_o;
	t_image_cub		*wall_s;
	t_image_cub		*wall_e;
	t_image_cub		*fog;
	t_image_cub		*potion;
	t_image_cub		*door;

	t_thread_manager	*thread_manager;
	int				(*doors)[100][4];
	int				(*items)[100][3];
	int				ground;
	int				ceil;
	int					fuel;
	char			**map;
	double			*r_h_tab;
	double			*cos_r_h_tab;
	size_t			created_at;
	size_t			last_move;
	size_t			fuel_time;
	short int		inputs[7];
	int				is_moving;
	int				count_lines;
	int				count_row;
	t_objects		**map_items;
	int					lock_mouse_x;
    int					lock_mouse_y;
    int					is_mouse_locked;
    int					mouse_left_pressed;
}	t_main_struct;

typedef struct s_object_hit
{
	int				map_x;
	int				map_y;
	double			dist;
	double			height;
	int				text_x;
	int 			side;
	double			wall_pc;
	double			texpos;
	double			step;
	int				height_check_minus;
	int				height_check_plus;
	t_types_object	type;
	int				status;
	int				*line_add;
	t_image_cub		*texture;
}	t_object_hit;

typedef struct s_render_calculus
{
	double	res[4];
	double	height;
	int		text_x;
	int		text_y;
	double	step;
	double	texpos;
	int		height_check_minus;
	int		height_check_plus;
	double	wall_pc;
	double	teta;
	int		*line_add;
	t_object_hit	hit_tab[10];
	t_image_cub		*current_texture;
}	t_render_calculus;

typedef struct s_ray_calculus
{
	double			dir_x;
	double			dir_y;
	double			player_x;
	double			player_y;
	double			delta_x;
	double			delta_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	int				map_x;
	int				map_y;
	int		render_dist;
	double			wall_x;
	double			wall_y;
	double			dist;
	int				flag_dist;
	int				index_hit_tab;
}	t_ray_calculus;

#endif
