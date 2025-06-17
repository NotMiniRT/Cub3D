#ifndef MONSTER_H
# define MONSTER_H

# include "structs_b.h"

void move_monster(t_main_struct *main_struct);
void get_monster_dir(t_main_struct *main_struct);
bool set_mj(t_main_struct *main_struct, t_infos *infos);

#endif