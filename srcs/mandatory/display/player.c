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
	player->fov_angle = PIX05 + 0.001;
	return (1);
}

void	turn_player(t_player *player, int turn_dir)
{
	player->fov_angle += turn_dir * ROT_SPEED;
	if (player->fov_angle < 0)
		player->fov_angle += PIX2 - player->fov_angle;
	if (player->fov_angle > PIX2)
		player->fov_angle -= PIX2;
}

void	move_player(t_main_struct *main_struct, int move_dir_front,
		int move_dir_side)
{
	double	move_x;
	double	move_y;

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
		move_x = main_struct->player->x + cos(main_struct->player->fov_angle + PIX05) * move_dir_side * PLAYER_SPEED;
		move_y = main_struct->player->y + sin(main_struct->player->fov_angle + PIX05) * move_dir_side * PLAYER_SPEED;
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

void	player_log(t_main_struct *main_struct)
{
	printf("player: x: %f, y: %f, angle: %f\n", main_struct->player->x,
		main_struct->player->y, main_struct->player->fov_angle);
}
