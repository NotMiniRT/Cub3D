#include <math.h>

#include "common.h"
#include "structs_b.h"

void	define_basic_param_calculus(t_ray_calculus *calcul,
	double cos_sin[2], t_main_struct *main_struct)
{
	calcul->flag_dist = 0;
	calcul->render_dist = main_struct->fuel * RENDER_DIST;
	calcul->player_x = main_struct->player->x;
	calcul->player_y = main_struct->player->y;
	calcul->dir_x = cos_sin[0];
	calcul->dir_y = cos_sin[1];
	calcul->map_x = (int)floor(calcul->player_x);
	calcul->map_y = (int)floor(calcul->player_y);
	if (fabs(calcul->dir_x) < 0.000001)
		calcul->tilde_step_x = 10000000;
	else
		calcul->tilde_step_x = fabs(1.0 / calcul->dir_x);
	if (fabs(calcul->dir_y) < 0.000001)
		calcul->tilde_step_y = 10000000;
	else
		calcul->tilde_step_y = fabs(1.0 / calcul->dir_y);
	calcul->index_hit_tab = 0;
	calcul->step_x = 1 - (calcul->dir_x < 0) * 2;
	calcul->step_y = 1 - (calcul->dir_y < 0) * 2;
}

void	get_start_dist(t_ray_calculus *calcul)
{
	if (calcul->dir_x < 0)
		calcul->dist_x = (calcul->player_x - calcul->map_x)
			* calcul->tilde_step_x;
	else
		calcul->dist_x = (calcul->map_x + 1.0 - calcul->player_x)
			* calcul->tilde_step_x;
	if (calcul->dir_y < 0)
		calcul->dist_y = (calcul->player_y - calcul->map_y)
			* calcul->tilde_step_y;
	else
		calcul->dist_y = (calcul->map_y + 1.0 - calcul->player_y)
			* calcul->tilde_step_y;
	calcul->side = 0;
}

void	get_dists_and_wall_x_y(t_ray_calculus *calcul)
{
	if (calcul->side == 0)
	{
		calcul->wall_x = (calcul->map_x - calcul->player_x
				+ (1 - calcul->step_x) * 0.5);
		calcul->wall_y = ((calcul->map_x - calcul->player_x
					+ (1 - calcul->step_x) * 0.5)
				/ calcul->dir_x) * calcul->dir_y;
		calcul->dist = calcul->dist_x - calcul->tilde_step_x;
	}
	else
	{
		calcul->wall_x = ((calcul->map_y - calcul->player_y
					+ (1 - calcul->step_y) * 0.5)
				/ calcul->dir_y) * calcul->dir_x;
		calcul->wall_y = (calcul->map_y - calcul->player_y
				+ (1 - calcul->step_y) * 0.5);
		calcul->dist = calcul->dist_y - calcul->tilde_step_y;
	}
}