#ifndef LST_INT_H
# define LST_INT_H

# include "structs_b.h"

void add_front_lst_int(t_lst_int **list, int i);
void remove_last_lst_int(t_lst_int **list);
void free_lst_int(t_lst_int *list);

#endif