#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

# include "player.h"

typedef struct s_main_struct
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		*player;
} t_main_struct;

void	init_main_struct(t_main_struct *main_struct);
void	free_main_struct(t_main_struct *main_struct);

#endif
