#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

# include "struct_player.h"
# include "struct_image.h"
# include "stdlib.h"
# include "common.h"
typedef enum moves {
    UP = 0,
    DOWN = 1,
    RIGHT = 2,
    LEFT = 3,
    TRIGHT = 4,
    TLEFT = 5,
	SHIFT = 6
} moves;


typedef struct s_main_struct
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		*player;
	t_image_cub		*frame;
	t_image_cub		*wall;
	char			**map;	
	double			*R_H_tab;
	double			*cos_R_H_tab;
	size_t			created_at;
	size_t			last_move;
	short int		inputs[7];
	int 			is_moving;
} t_main_struct;

int		is_moving(t_main_struct *t_main_struct);
void	init_main_struct(t_main_struct *main_struct);
void	free_main_struct(t_main_struct *main_struct);
int		init_R_H_tab(t_main_struct *main_struct);
#endif
