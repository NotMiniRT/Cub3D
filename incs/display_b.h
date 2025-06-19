#ifndef DISPLAY_B_H
# define DISPLAY_B_H

# include "main_struct_b.h"
# include "parsing.h"
# include <stdbool.h>

int		frame_display(t_main_struct *main_struct);
int		mlx_loop_action(t_main_struct *main_struct);
bool	start_display(t_main_struct *main_struct, t_infos *infos);

bool	init_all_sprites(t_main_struct *main_struct, t_infos *infos);

#endif
