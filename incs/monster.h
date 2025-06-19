#ifndef MONSTER_H
# define MONSTER_H

# define MJ_NO_NB "assets/textures/mj/mj-"

typedef struct s_main_struct	t_main_struct;
typedef struct s_infos			t_infos;

void	move_monster(t_main_struct *main_struct);
void	get_monster_dir(t_main_struct *main_struct);
bool	set_mj(t_main_struct *main_struct, t_infos *infos);

#endif
