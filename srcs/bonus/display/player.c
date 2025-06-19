#include <math.h>

#include "common.h"
#include "doors_b.h"
#include "parsing.h"
#include "sound.h"
#include "structs_b.h"
#include "player_b.h"

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
