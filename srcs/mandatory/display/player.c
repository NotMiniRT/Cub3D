#include "player.h"
#include "common.h"
#include <math.h>
#include <stdio.h>
#include "ray.h"
#include "main_struct.h"
#include "struct_player.h"
int	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->fov_angle = 0.5 * PI;
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

void move_foward_backward(t_main_struct *main_struct, int move_dir)
{
	float move_x;
	float move_y;

	move_x = main_struct->player->x + move_dir * (cos(main_struct->player->fov_angle) * PLAYER_SPEED);
	move_y = main_struct->player->y + move_dir * (sin(main_struct->player->fov_angle) * PLAYER_SPEED);
	if (main_struct->map[(int)move_y][(int)move_x] != '1')
	{
		main_struct->player->x = move_x;
		main_struct->player->y = move_y;
	}
	else if (main_struct->map[(int)move_y][(int)main_struct->player->x] != '1')
		main_struct->player->y = move_y;
	else if (main_struct->map[(int)main_struct->player->y][(int)move_x] != '1')
		main_struct->player->x = move_x;
}

void move_left_right(t_main_struct *main_struct, int move_dir)
{
	float move_x;
	float move_y;

	move_x = main_struct->player->x + cos(main_struct->player->fov_angle + PI * 0.5) * move_dir * PLAYER_SPEED;
	move_y = main_struct->player->y + sin(main_struct->player->fov_angle + PI * 0.5) * move_dir * PLAYER_SPEED;
	if (main_struct->map[(int)move_y][(int)move_x] != '1')
	{
		main_struct->player->x = move_x;
		main_struct->player->y = move_y;
	}
	else if (main_struct->map[(int)move_y][(int)main_struct->player->x] != '1')
		main_struct->player->y = move_y;
	else if (main_struct->map[(int)main_struct->player->y][(int)move_x] != '1')
		main_struct->player->x = move_x;
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

void	player_log(t_main_struct *main_struct)
{
	// float	cross[2];
	printf("player: x: %f, y: %f, angle: %f\n", main_struct->player->x, main_struct->player->y, main_struct->player->fov_angle);
	// cross[0] = main_struct->player->x;
	// cross[1] = 0;
	// ray_check(main_struct, &cross);
	// printf("First colision at %f, it's a %c\n", cross[0], 'x' + (cross[1] >= 1));
}