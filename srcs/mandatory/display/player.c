#include "player.h"
#include "common.h"
#include <math.h>
#include <stdio.h>
#include "ray.h"
#include "main_struct.h"

int	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->fov_angle =  0.5 * PI + 0.001;
	return (1);
}

void turn_player(t_player *player, int turn_dir)
{
	player->fov_angle += turn_dir * ROT_SPEED;
	if (player->fov_angle < 0)
		player->fov_angle += PIx2 - player->fov_angle;
	if (player->fov_angle > PIx2)
		player->fov_angle -= PIx2;
}

void move_player(t_main_struct *main_struct, int move_dir_front, int move_dir_side)
{
	double move_x;
	double move_y;

	if (move_dir_front != 0)
	{
		move_x = main_struct->player->x + (1 + 2 * (main_struct->inputs[SHIFT] == 1)) * move_dir_front * (cos(main_struct->player->fov_angle) * PLAYER_SPEED);
		move_y = main_struct->player->y + (1 + 2 * (main_struct->inputs[SHIFT] == 1)) * move_dir_front * (sin(main_struct->player->fov_angle) * PLAYER_SPEED);
		if (main_struct->map[(int)move_y][(int)move_x] != '1' && main_struct->map[(int)move_y][(int)main_struct->player->x] != '1' && main_struct->map[(int)main_struct->player->y][(int)move_x] != '1')
		{
			main_struct->player->x = move_x;
			main_struct->player->y = move_y;
		}
		else if (main_struct->map[(int)move_y][(int)main_struct->player->x] != '1')
		{
			if (main_struct->player->x - move_x < 0)
				main_struct->player->x = floor(move_x) - 0.01;
			else if (main_struct->player->x - move_x > 0)
				main_struct->player->x = ceil(move_x) + 0.01;
			main_struct->player->y = move_y;
		}
		else if (main_struct->map[(int)main_struct->player->y][(int)move_x] != '1')
		{			
			main_struct->player->x = move_x;
			if (main_struct->player->y - move_y < 0)
				main_struct->player->y = floor(move_y) - 0.01;
			else if (main_struct->player->y - move_y > 0)
				main_struct->player->y = ceil(move_y) + 0.01;
		}
	}
	if (move_dir_side != 0)
	{
		move_x = main_struct->player->x + cos(main_struct->player->fov_angle + PI * 0.5) * move_dir_side * PLAYER_SPEED;
		move_y = main_struct->player->y + sin(main_struct->player->fov_angle + PI * 0.5) * move_dir_side * PLAYER_SPEED;
		if (main_struct->map[(int)move_y][(int)move_x] != '1' && main_struct->map[(int)move_y][(int)main_struct->player->x] != '1' && main_struct->map[(int)main_struct->player->y][(int)move_x] != '1')
		{
			main_struct->player->x = move_x;
			main_struct->player->y = move_y;
		}
		else if (main_struct->map[(int)move_y][(int)main_struct->player->x] != '1')
		{
			if (main_struct->player->x - move_x < 0)
				main_struct->player->x = floor(move_x) - 0.01;
			else if (main_struct->player->x - move_x > 0)
				main_struct->player->x = ceil(move_x) + 0.01;
			main_struct->player->y = move_y;
		}
		else if (main_struct->map[(int)main_struct->player->y][(int)move_x] != '1')
		{			
			main_struct->player->x = move_x;
			if (main_struct->player->y - move_y < 0)
				main_struct->player->y = floor(move_y) - 0.01;
			else if (main_struct->player->y - move_y > 0)
				main_struct->player->y = ceil(move_y) + 0.01;
		}
	}
}

int	is_facing_up(double ray_angle)
{
	return (ray_angle > PI);
}
int	is_facing_left(double ray_angle)
{
	return (ray_angle > PIx05 && ray_angle < PIx15 );
}
int	is_facing_right(double ray_angle)
{
	return (!is_facing_left(ray_angle));
}

int	is_facing_down(double ray_angle)
{
	return (!is_facing_up(ray_angle));
}

void	player_log(t_main_struct *main_struct)
{
	// double	cross[2];
	printf("player: x: %f, y: %f, angle: %f\n", main_struct->player->x, main_struct->player->y, main_struct->player->fov_angle);
	// cross[0] = main_struct->player->x;
	// cross[1] = 0;
	// ray_check(main_struct, &cross);
	// printf("First colision at %f, it's a %c\n", cross[0], 'x' + (cross[1] >= 1));
}