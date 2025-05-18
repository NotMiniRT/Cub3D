#ifndef INPUTS_H
# define INPUTS_H

# include "structs.h"

int	on_destroy(t_main_struct *main_struct);
int	handle_input(int keysym, t_main_struct *main_struct);
int	release_move(int keysym, t_main_struct *main_struct);

int	handle_mouse_move(int x, int y, t_main_struct *main_struct);
int	handle_mouse_press(int button, int x, int y, t_main_struct *main_struct);
int	handle_mouse_rl(int button, int x, int y, t_main_struct *main_struct);

#endif
