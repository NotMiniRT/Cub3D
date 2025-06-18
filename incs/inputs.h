#ifndef INPUTS_H
# define INPUTS_H

typedef struct s_main_struct	t_main_struct;

int	on_destroy(t_main_struct *main_struct);
int	handle_input(int keysym, t_main_struct *main_struct);
int	release_move(int keysym, t_main_struct *main_struct);

#endif
