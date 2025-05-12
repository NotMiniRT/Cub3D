#ifndef DISPLAY_H
# define DISPLAY_H

# include <stdbool.h>

# include "main_struct.h"
# include "parsing.h"

int	frame_display(t_main_struct *main_struct);
int	mlx_loop_action(t_main_struct *main_struct);
int	start_display(t_main_struct *main_struct, t_infos *infos);

#endif
