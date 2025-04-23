#include "player.h"
#include "common.h"
#include <math.h>
#include <stdio.h>

int	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->fov_angle = 0;
	return (1);
}

void turn(t_player *player, int turn_dir)
{
	player->fov_angle += turn_dir * ROT_SPEED;
	if (player->fov_angle > 2 * PI)
		player->fov_angle -= 2 * PI;
	if (player->fov_angle < -2 * PI)
		player->fov_angle += 2 * PI;
}

void move_foward_backward(t_player *player, int move_dir)
{
	player->x += move_dir * (cos(player->fov_angle) * PLAYER_SPEED);
	player->y += move_dir * (sin(player->fov_angle) * PLAYER_SPEED);
}

void move_left_right(t_player *player, int move_dir)
{
	player->x += cos(player->fov_angle + PI * 0.5) * move_dir * PLAYER_SPEED;
	player->y += sin(player->fov_angle + PI * 0.5) * move_dir * PLAYER_SPEED;
}
int	is_facing_down(float ray_angle)
{
	if (ray_angle < 0)
	{
		printf("from %f to %f\n", ray_angle, 2 * PI + ray_angle);
		ray_angle = 2 * PI + ray_angle;
	}
	return (ray_angle < PI);
}
int	is_facing_left(float ray_angle)
{
	if (ray_angle < 0)
		ray_angle = 2 * PI + ray_angle;
	return (ray_angle < PI * 0.5 || ray_angle > PI * 1.5 );
}
int	is_facing_right(float ray_angle)
{
	return (!is_facing_left(ray_angle));
}

int	is_facing_up(float ray_angle)
{
	return (!is_facing_down(ray_angle));
}

void	player_log(t_player *player)
{
	printf("player: x: %f, y: %f, angle: %f\n", player->x, player->y, player->fov_angle);
	if (is_facing_down(player->fov_angle))
		printf("player is facing down ");
	else
		printf("player is facing up ");
	if (is_facing_left(player->fov_angle))
		printf("and left\n");
	else
		printf("and right\n");
}