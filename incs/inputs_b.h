#ifndef INPUTS_B_H
# define INPUTS_B_H

# include "structs_b.h"

int	on_destroy(t_main_struct *main_struct);
int	handle_input(int keysym, t_main_struct *main_struct);
int	release_move(int keysym, t_main_struct *main_struct);

#endif
