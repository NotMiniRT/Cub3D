#ifndef DOORS_B_H
# define DOORS_B_H

# include "structs_b.h"

int	get_status_door(int x, int y, t_main_struct *main_struct);
void up_doors(t_main_struct *main_struct, t_lst_int **lst);
void down_doors(t_main_struct *main_struct, t_lst_int **lst);
#endif