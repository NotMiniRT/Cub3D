#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

typedef struct s_main_struct	t_main_struct;

int		is_moving(t_main_struct *t_main_struct);
void	free_main_struct(t_main_struct *main_struct);
int		init_r_h_tab(t_main_struct *main_struct);

#endif
