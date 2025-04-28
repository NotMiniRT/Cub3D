#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player
{
	float x;
	float y;
	float fov_angle;
} t_player;

int	is_facing_up(float ray_angle);
int	is_facing_down(float ray_angle);
int	is_facing_left(float ray_angle);
int	is_facing_right(float ray_angle);
int	init_player(t_player *player);
void turn(t_player *player, int turn_dir);
void move_foward_backward(t_player *player, int move_dir);
void move_left_right(t_player *player, int move_dir);

#endif