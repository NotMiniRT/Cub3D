#include <math.h>

#include "common.h"
#include "doors_b.h"
#include "parsing.h"
#include "sound.h"
#include "structs_b.h"

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

static void	one_direction(t_main_struct *ms, double move_x,
		double move_y)
{
	if (ms->map[(int)move_y][(int)move_x] != '1'
		&& ms->map[(int)move_y][(int)ms->player->x] != '1'
		&& ms->map[(int)ms->player->y][(int)move_x] != '1'
		&& (ms->map[(int)move_y][(int)ms->player->x] != 'D'
		|| get_status_door((int)move_y, (int)ms->player->x, ms) == 0)
		&& (ms->map[(int)ms->player->y][(int)move_x] != 'D'
		|| get_status_door((int)ms->player->y, (int)move_x, ms) == 0)
		&& (ms->map[(int)move_y][(int)move_x] != 'D'
		|| get_status_door((int)move_y, (int)move_x, ms) == 0))
	{
		ms->player->x = move_x;
		ms->player->y = move_y;
	}
	else if (ms->map[(int)move_y][(int)ms->player->x] != '1'
		&& (ms->map[(int)move_y][(int)ms->player->x] != 'D'
		|| get_status_door((int)move_y, (int)ms->player->x, ms) == 0))
	{
		if (ms->player->x - move_x < 0)
			ms->player->x = floor(move_x) - 0.01;
		else if (ms->player->x - move_x > 0)
			ms->player->x = ceil(move_x) + 0.01;
		ms->player->y = move_y;
	}
	else if (ms->map[(int)ms->player->y][(int)move_x] != '1'
			&& (ms->map[(int)ms->player->y][(int)move_x] != 'D'
			|| get_status_door((int)ms->player->y, (int)move_x, ms) == 0))
	{
		ms->player->x = move_x;
		if (ms->player->y - move_y < 0)
			ms->player->y = floor(move_y) - 0.01;
		else if (ms->player->y - move_y > 0)
			ms->player->y = ceil(move_y) + 0.01;
	}
	if (ms->map[(int)ms->player->y][(int)ms->player->x] == 'C')
	{
		play_sound(ms, SOUND_PICKUP);
		ms->map[(int)ms->player->y][(int)ms->player->x] = '0';
		ms->collectible_count = ms->collectible_count - 1;
		if (ms->collectible_count == 0)
			ms->died = 1;
		if (ms->fuel <= 0.9)
			ms->fuel = ms->fuel + 0.1;
		else
			ms->fuel = 1;
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
