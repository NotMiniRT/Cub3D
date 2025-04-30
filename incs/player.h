#ifndef PLAYER_H
# define PLAYER_H

#include "main_struct.h"
#include "struct_player.h"

int	is_facing_up(float ray_angle);
int	is_facing_down(float ray_angle);
int	is_facing_left(float ray_angle);
int	is_facing_right(float ray_angle);
int	init_player(t_player *player);
void turn(t_player *player, int turn_dir);
void move_foward_backward(t_main_struct *main_struct, int move_dir);
void move_left_right(t_main_struct *main_struct, int move_dir);

#endif