#ifndef MAIN_STRUCT_B_H
# define MAIN_STRUCT_B_H

# include "structs_b.h"
# include <stdbool.h>

int		is_moving(t_main_struct *t_main_struct);
void	free_main_struct_first_part(t_main_struct *main_struct);
int		init_r_h_tab(t_main_struct *main_struct);
bool	map_object_set(t_main_struct *main_struct);
void	free_map_item_ij(t_main_struct *main_struct);

#endif
