#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

# include "structs.h"

int		is_moving(t_main_struct *t_main_struct);
void	init_main_struct(t_main_struct *main_struct);
void	free_main_struct(t_main_struct *main_struct);
int		init_R_H_tab(t_main_struct *main_struct);
#endif
