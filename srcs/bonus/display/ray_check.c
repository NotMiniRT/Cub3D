/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:43:56 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:43:57 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ray_b.h"

static void	fill_cross(t_ray_calculus *calcul, double (*cross)[5],
	t_object_hit	hit_tab[HIT_TAB_LEN])
{
	(*cross)[0] = calcul->dist;
	(*cross)[1] = calcul->side;
	if (calcul->flag_dist)
	{
		(*cross)[0] = calcul->render_dist;
		(*cross)[1] = 0;
	}
	if (calcul->side == 1)
		(*cross)[2] = calcul->player_x + calcul->wall_x;
	else
		(*cross)[2] = calcul->player_y + calcul->wall_y;
	(*cross)[3] = calcul->flag_dist;
	(*cross)[4] = calcul->index_hit_tab;
	if (calcul->dist_mj > 0 && (*cross)[0] > calcul->dist_mj)
	{
		add_mj(calcul, hit_tab);
		(*cross)[4] = calcul->index_hit_tab;
	}
}

void	increment_ray(t_main_struct *main_struct,
	t_ray_calculus	*calcul,
	double cos_sin[2], t_object_hit	hit_tab[HIT_TAB_LEN])
{
	calcul->flag_dist
		= (calcul->dist_x > calcul->render_dist
			&& calcul->dist_y > calcul->render_dist);
	if (main_struct->map[calcul->map_y][calcul->map_x] == 'D')
		add_hit_ray_door(calcul, hit_tab, main_struct, cos_sin);
	else if (main_struct->map[calcul->map_y][calcul->map_x] == 'C')
		add_hit_ray_item(calcul, hit_tab, main_struct, cos_sin);
	if (calcul->dist_x < calcul->dist_y)
	{
		calcul->dist_x += calcul->tilde_step_x;
		calcul->map_x += calcul->step_x;
		calcul->side = 0;
	}
	else
	{
		calcul->dist_y += calcul->tilde_step_y;
		calcul->map_y += calcul->step_y;
		calcul->side = 1;
	}
}

void	ray_check(t_main_struct *main_struct,
		double (*cross)[5],
		double cos_sin[2], t_object_hit	hit_tab[HIT_TAB_LEN])
{
	t_ray_calculus	calcul;

	define_basic_param_calculus(&calcul, cos_sin, main_struct);
	get_start_dist(&calcul);
	if (main_struct->mj != NULL)
		calcul.dist_mj = get_monster_dist(&calcul, main_struct, cos_sin);
	else
		calcul.dist_mj = -1;
	while (!calcul.flag_dist
		&& main_struct->map[calcul.map_y][calcul.map_x] != '1')
		increment_ray(main_struct, &calcul, cos_sin, hit_tab);
	get_dists_and_wall_x_y(&calcul);
	fill_cross(&calcul, cross, hit_tab);
}
