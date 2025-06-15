#include "structs_b.h"
#include "common.h"
#include <math.h>
#include "ray_b.h"
#include "parsing.h"
#include "doors_b.h"

int	init_player(t_player *player, t_infos *infos)
{
	player->x = infos->scene->pos[0] - 0.5;
	player->y = infos->scene->pos[1] - 0.5;
	if (infos->scene->pos[2] == 'N')
		player->fov_angle = PIXX15 + 0.001;
	else if (infos->scene->pos[2] == 'E')
		player->fov_angle = 0.001;
	else if (infos->scene->pos[2] == 'S')
		player->fov_angle = PIX2 + 0.001;
	else
		player->fov_angle = PI + 0.001;
	return (1);
}

void	rotate_player_by_mouse(t_player *player, double rotation)
{
	player->fov_angle += rotation;
	if (player->fov_angle < 0)
		player->fov_angle += PIXX2;
	if (player->fov_angle > PIXX2)
		player->fov_angle -= PIXX2;
}

void	turn_player(t_player *player, int turn_dir)
{
	player->fov_angle += turn_dir * ROT_SPEED;
	if (player->fov_angle < 0)
		player->fov_angle += PIXX2 - player->fov_angle;
	if (player->fov_angle > PIXX2)
		player->fov_angle -= PIXX2;
}

static void	one_direction(t_main_struct *main_struct, double move_x,
		double move_y)
{
	if (main_struct->map[(int)move_y][(int)move_x] != '1'
		&& main_struct->map[(int)move_y][(int)main_struct->player->x] != '1'
		&& main_struct->map[(int)main_struct->player->y][(int)move_x] != '1'
		&& (main_struct->map[(int)move_y][(int)main_struct->player->x] != 'D'
		|| get_status_door((int)move_y, (int)main_struct->player->x, main_struct) == 0)
		&& (main_struct->map[(int)main_struct->player->y][(int)move_x] != 'D'
		|| get_status_door((int)main_struct->player->y, (int)move_x, main_struct) == 0)
		&& (main_struct->map[(int)move_y][(int)move_x] != 'D'
		|| get_status_door((int)move_y, (int)move_x, main_struct) == 0))
	{
		main_struct->player->x = move_x;
		main_struct->player->y = move_y;
	}
	else if (main_struct->map[(int)move_y][(int)main_struct->player->x] != '1'
		&& (main_struct->map[(int)move_y][(int)main_struct->player->x] != 'D'
		|| get_status_door((int)move_y, (int)main_struct->player->x, main_struct) == 0))
	{
		if (main_struct->player->x - move_x < 0)
			main_struct->player->x = floor(move_x) - 0.01;
		else if (main_struct->player->x - move_x > 0)
			main_struct->player->x = ceil(move_x) + 0.01;
		main_struct->player->y = move_y;
	}
	else if (main_struct->map[(int)main_struct->player->y][(int)move_x] != '1'
			&& (main_struct->map[(int)main_struct->player->y][(int)move_x] != 'D'
			|| get_status_door((int)main_struct->player->y, (int)move_x, main_struct) == 0))
	{
		main_struct->player->x = move_x;
		if (main_struct->player->y - move_y < 0)
			main_struct->player->y = floor(move_y) - 0.01;
		else if (main_struct->player->y - move_y > 0)
			main_struct->player->y = ceil(move_y) + 0.01;
	}
	if (main_struct->map[(int)main_struct->player->y][(int)main_struct->player->x] == 'C')
	{
		main_struct->map[(int)main_struct->player->y][(int)main_struct->player->x] = '0';
		main_struct->collectible_count = main_struct->collectible_count - 1;
		if (main_struct->collectible_count == 0)
			main_struct->died = 1;
		if (main_struct->fuel <= 0.9)
			main_struct->fuel = main_struct->fuel + 0.1;
		else
			main_struct->fuel = 1;
	}
}

void	move_player(t_main_struct *main_struct, int move_dir_front,
		int move_dir_side)
{
	double	move_x;
	double	move_y;

	if (move_dir_front != 0)
	{
		move_x = main_struct->player->x + (1 + 2 \
			* (main_struct->inputs[SHIFT] == 1)) * move_dir_front
			* (cos(main_struct->player->fov_angle) * PLAYER_SPEED);
		move_y = main_struct->player->y + (1 + 2 \
			* (main_struct->inputs[SHIFT] == 1)) * move_dir_front
			* (sin(main_struct->player->fov_angle) * PLAYER_SPEED);
		one_direction(main_struct, move_x, move_y);
	}
	if (move_dir_side != 0)
	{
		move_x = main_struct->player->x + cos(main_struct->player->fov_angle \
					+ PIX2) * move_dir_side * PLAYER_SPEED;
		move_y = main_struct->player->y + sin(main_struct->player->fov_angle \
					+ PIX2) * move_dir_side * PLAYER_SPEED;
		one_direction(main_struct, move_x, move_y);
	}
}
