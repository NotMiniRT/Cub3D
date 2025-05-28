#ifndef PLAYER_B_H
# define PLAYER_B_H

# include "structs_b.h"
# include "parsing.h"

int		is_facing_up(double ray_angle);
int		is_facing_down(double ray_angle);
int		is_facing_left(double ray_angle);
int		is_facing_right(double ray_angle);
int		init_player(t_player *player, t_infos *infos);
void	turn_player(t_player *player, int turn_dir);
void	move_player(t_main_struct *main_struct,
			int move_dir_front, int move_dir_side);
void open_door(t_main_struct *main_struct);
void	rotate_player_by_mouse(t_player *player, double rotation);

#endif
