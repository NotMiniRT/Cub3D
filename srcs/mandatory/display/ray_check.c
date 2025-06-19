#include "structs.h"
#include "math.h"
#include "common.h"

static void	define_basic_param_calculus(t_ray_calculus *calcul,
		double cos_sin[2], t_main_struct *main_struct)
{
	calcul->flag_dist = 0;
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
}

static void	get_step_and_side_dist(t_ray_calculus *calcul)
{
	calcul->step_x = 1 - (calcul->dir_x < 0) * 2;
	calcul->step_y = 1 - (calcul->dir_y < 0) * 2;
	if (calcul->dir_x < 0)
		calcul->side_dist_x = (calcul->player_x - calcul->map_x)
			* calcul->tilde_step_x;
	else
		calcul->side_dist_x = (calcul->map_x + 1.0 - calcul->player_x)
			* calcul->tilde_step_x;
	if (calcul->dir_y < 0)
		calcul->side_dist_y = (calcul->player_y - calcul->map_y)
			* calcul->tilde_step_y;
	else
		calcul->side_dist_y = (calcul->map_y + 1.0 - calcul->player_y)
			* calcul->tilde_step_y;
	calcul->side = 0;
}

static void	get_dists_and_wall_x_y(t_ray_calculus *calcul)
{
	if (calcul->side == 0)
	{
		calcul->wall_x = (calcul->map_x - calcul->player_x
				+ (1 - calcul->step_x) * 0.5);
		calcul->wall_y = ((calcul->map_x - calcul->player_x
					+ (1 - calcul->step_x) * 0.5)
				/ calcul->dir_x) * calcul->dir_y;
		calcul->dist = calcul->side_dist_x - calcul->tilde_step_x;
	}
	else
	{
		calcul->wall_x = ((calcul->map_y - calcul->player_y
					+ (1 - calcul->step_y) * 0.5)
				/ calcul->dir_y) * calcul->dir_x;
		calcul->wall_y = (calcul->map_y - calcul->player_y
				+ (1 - calcul->step_y) * 0.5);
		calcul->dist = calcul->side_dist_y - calcul->tilde_step_y;
	}
}

static void	fill_cross(t_ray_calculus *calcul, double (*cross)[4])
{
	(*cross)[0] = calcul->dist;
	(*cross)[1] = calcul->side;
	if (calcul->flag_dist)
	{
		(*cross)[0] = RENDER_DIST;
		(*cross)[1] = 0;
	}
	if (calcul->side == 1)
		(*cross)[2] = calcul->player_x + calcul->wall_x;
	else
		(*cross)[2] = calcul->player_y + calcul->wall_y;
	(*cross)[3] = calcul->flag_dist;
}

void	ray_check(t_main_struct *main_struct,
		double (*cross)[4], double cos_sin[2])
{
	t_ray_calculus	calcul;

	define_basic_param_calculus(&calcul, cos_sin, main_struct);
	get_step_and_side_dist(&calcul);
	while (!calcul.flag_dist
		&& main_struct->map[calcul.map_y][calcul.map_x] != '1')
	{
		calcul.flag_dist
			= (calcul.side_dist_x > RENDER_DIST
				&& calcul.side_dist_y > RENDER_DIST);
		if (calcul.side_dist_x < calcul.side_dist_y)
		{
			calcul.side_dist_x += calcul.tilde_step_x;
			calcul.map_x += calcul.step_x;
			calcul.side = 0;
		}
		else
		{
			calcul.side_dist_y += calcul.tilde_step_y;
			calcul.map_y += calcul.step_y;
			calcul.side = 1;
		}
	}
	get_dists_and_wall_x_y(&calcul);
	fill_cross(&calcul, cross);
}
