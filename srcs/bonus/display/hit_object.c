#include <math.h>

#include "structs_b.h"
#include "ray_b.h"

void	add_door(t_ray_calculus *calcul,
	t_object_hit *door, t_point p3, t_point inter)
{
	door->wall_pc = dist_points(p3, inter);
	door->map_x = calcul->map_y;
	door->map_y = calcul->map_x;
	door->type = DOOR;
	door->side = calcul->side;
	calcul->index_hit_tab++;
}

void	add_hit_ray_door(t_ray_calculus *calcul,
	t_object_hit hit_tab[HIT_TAB_LEN],
	t_main_struct *main_struct, double cos_sin[2])
{
	t_object_door	*d;
	t_point			p1;
	t_point			p3;
	t_point			inter;

	if (calcul->index_hit_tab >= HIT_TAB_LEN - 1)
		return ;
	d = main_struct->map_items[calcul->map_y + 1][calcul->map_x + 1].door;
	p1 = (t_point){.x = calcul->player_x, .y = calcul->player_y};
	p3 = (t_point){.x = d->p1.x -1, .y = d->p1.y -1};
	inter = calcul_intersection(p1, (t_point){.x = calcul->player_x + cos_sin[0]
			* calcul->render_dist, .y = calcul->player_y + cos_sin[1]
			* calcul->render_dist}, p3,
			(t_point){.x = d->p2.x - 1, .y = d->p2.y - 1});
	if (inter.x == -1)
		return ;
	hit_tab[calcul->index_hit_tab].dist = dist_points(p1, inter);
	if (calcul->dist_mj > 0
		&& calcul->dist_mj < hit_tab[calcul->index_hit_tab].dist)
	{
		hit_tab[calcul->index_hit_tab + 1].dist
			= hit_tab[calcul->index_hit_tab].dist;
		add_mj(calcul, hit_tab);
	}
	add_door(calcul, &hit_tab[calcul->index_hit_tab], p3, inter);
}

void	add_item(t_ray_calculus *calcul,
	t_object_hit *item, t_point p3, t_point inter)
{
	item->wall_pc = dist_points(p3, inter);
	item->map_x = calcul->map_y;
	item->map_y = calcul->map_x;
	item->type = ITEM;
	item->side = calcul->side;
	calcul->index_hit_tab++;
}

void	add_hit_ray_item(t_ray_calculus *calcul,
	t_object_hit hit_tab[HIT_TAB_LEN],
	t_main_struct *main_struct, double cos_sin[2])
{
	t_object_collectible	*item;
	t_point					p1;
	t_point					p3;
	t_point					inter;

	if (calcul->index_hit_tab >= HIT_TAB_LEN - 1)
		return ;
	item = main_struct->map_items[calcul->map_y + 1][calcul->map_x + 1].item;
	p1 = (t_point){.x = calcul->player_x, .y = calcul->player_y};
	p3 = (t_point){.x = item->p1.x -1, .y = item->p1.y -1};
	inter = calcul_intersection(p1, (t_point){.x = calcul->player_x + cos_sin[0]
			* calcul->render_dist, .y = calcul->player_y + cos_sin[1]
			* calcul->render_dist}, p3,
			(t_point){.x = item->p2.x -1, .y = item->p2.y -1});
	if (inter.x == -1)
		return ;
	hit_tab[calcul->index_hit_tab].dist = dist_points(p1, inter);
	if (calcul->dist_mj > 0
		&& calcul->dist_mj < hit_tab[calcul->index_hit_tab].dist)
	{
		hit_tab[calcul->index_hit_tab + 1].dist
			= hit_tab[calcul->index_hit_tab].dist;
		add_mj(calcul, hit_tab);
	}
	add_item(calcul, &hit_tab[calcul->index_hit_tab], p3, inter);
}

double	get_monster_dist(t_ray_calculus *calcul,
	t_main_struct *main_struct, double cos_sin[2])
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;
	t_point	inter;

	if (calcul->index_hit_tab >= HIT_TAB_LEN)
		return (-1);
	p1.x = calcul->player_x;
	p1.y = calcul->player_y;
	p2.x = calcul->player_x + cos_sin[0] * calcul->render_dist;
	p2.y = calcul->player_y + cos_sin[1] * calcul->render_dist;
	p3.x = main_struct->mj->p1.x;
	p3.y = main_struct->mj->p1.y;
	p4.x = main_struct->mj->p2.x;
	p4.y = main_struct->mj->p2.y;
	inter = calcul_intersection(p1, p2, p3, p4);
	if (inter.x == -1)
	{
		calcul->wall_pc_mj = -1;
		return (-1);
	}
	calcul->wall_pc_mj = dist_points(p3, inter);
	return (dist_points(p1, inter));
}
