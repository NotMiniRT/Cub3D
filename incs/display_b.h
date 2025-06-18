#ifndef DISPLAY_B_H
# define DISPLAY_B_H

# include <stdbool.h>

# include "main_struct_b.h"
# include "parsing.h"

typedef struct s_main_struct	t_main_struct;

int		frame_display(t_main_struct *main_struct);
int		mlx_loop_action(t_main_struct *main_struct);
bool	start_display(t_main_struct *main_struct, t_infos *infos);

bool	init_all_sprites(t_main_struct *main_struct, t_infos *infos);

#endif
