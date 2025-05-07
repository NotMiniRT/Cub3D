#ifndef DISPLAY_H
# define DISPLAY_H

# include <stdbool.h>

# include "main_struct.h"

int	frame_display(t_main_struct *main_struct);
int	mlx_loop_action(t_main_struct *main_struct);
bool	start_display(t_main_struct *main_struct);

#endif
