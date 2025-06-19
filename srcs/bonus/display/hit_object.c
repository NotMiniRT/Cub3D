#include "structs_b.h"

static t_point	calcul_intersection(t_point p1,
	t_point p2, t_point p3, t_point p4)
{
	t_point	res;
	double	t;
	double	u;
	double	den;

	den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	if (den == 0)
	{
		res.x = -1;
		res.y = -1;
		return (res);
	}
	t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / den;
	u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / den;
	if (t > 0 && t < 1 && u > 0 && u < 1)
	{
		res.x = p1.x + t * (p2.x - p1.x);
		res.y = p1.y + t * (p2.y - p1.y);
		return (res);
	}
	res.x = -1;
	res.y = -1;
	return (res);
}

static inline double	dist_points(t_point a, t_point b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}


void	add_mj(t_ray_calculus *calcul, t_object_hit	hit_tab[HIT_TAB_LEN])
{
	hit_tab[calcul->index_hit_tab].dist = calcul->dist_mj;
	hit_tab[calcul->index_hit_tab].wall_pc = calcul->wall_pc_mj;
	hit_tab[calcul->index_hit_tab].map_x = calcul->map_y;
	hit_tab[calcul->index_hit_tab].map_y = calcul->map_x;
	hit_tab[calcul->index_hit_tab].type = MONSTER;
	hit_tab[calcul->index_hit_tab].side = 0;
	calcul->index_hit_tab++;
}


void	add_hit_ray_door(t_ray_calculus *calcul,
	t_object_hit hit_tab[HIT_TAB_LEN],
	t_main_struct *main_struct, double cos_sin[2])
{
	t_object_door	*door;
	t_point			p1;
	t_point			p2;
	t_point			p3;
	t_point			p4;
	t_point			inter;

	if (calcul->index_hit_tab >= HIT_TAB_LEN - 1)
		return ;
	door = main_struct->map_items[calcul->map_y + 1][calcul->map_x + 1].door;
	p1.x = calcul->player_x;
	p1.y = calcul->player_y;
	p2.x = calcul->player_x + cos_sin[0] * calcul->render_dist;
	p2.y = calcul->player_y + cos_sin[1] * calcul->render_dist;
	p3.x = door->p1.x -1;
	p3.y = door->p1.y -1;
	p4.x = door->p2.x -1;
	p4.y = door->p2.y -1;
	inter = calcul_intersection(p1, p2, p3, p4);
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
	hit_tab[calcul->index_hit_tab].wall_pc = dist_points(p3, inter);
	hit_tab[calcul->index_hit_tab].map_x = calcul->map_y;
	hit_tab[calcul->index_hit_tab].map_y = calcul->map_x;
	hit_tab[calcul->index_hit_tab].type = DOOR;
	hit_tab[calcul->index_hit_tab].side = calcul->side;
	calcul->index_hit_tab++;
}

void	add_hit_ray_item(t_ray_calculus *calcul,
	t_object_hit hit_tab[HIT_TAB_LEN],
	t_main_struct *main_struct, double cos_sin[2])
{
	t_object_collectible	*item;
	t_point					p1;
	t_point					p2;
	t_point					p3;
	t_point					p4;
	t_point					inter;

	if (calcul->index_hit_tab >= HIT_TAB_LEN - 1)
		return ;
	item = main_struct->map_items[calcul->map_y + 1][calcul->map_x + 1].item;
	p1.x = calcul->player_x;
	p1.y = calcul->player_y;
	p2.x = calcul->player_x + cos_sin[0] * calcul->render_dist;
	p2.y = calcul->player_y + cos_sin[1] * calcul->render_dist;
	p3.x = item->p1.x -1;
	p3.y = item->p1.y -1;
	p4.x = item->p2.x -1;
	p4.y = item->p2.y -1;
	inter = calcul_intersection(p1, p2, p3, p4);
	if (inter.x == -1)
		return ;
	hit_tab[calcul->index_hit_tab].dist = dist_points(p1, inter);
	if (calcul->dist_mj > 0
		&& calcul->dist_mj < hit_tab[calcul->index_hit_tab].dist)
	{
		add_mj(calcul, hit_tab);
		hit_tab[calcul->index_hit_tab].dist = dist_points(p1, inter);
	}
	hit_tab[calcul->index_hit_tab].wall_pc = dist_points(p3, inter);
	hit_tab[calcul->index_hit_tab].map_x = calcul->map_y;
	hit_tab[calcul->index_hit_tab].map_y = calcul->map_x;
	hit_tab[calcul->index_hit_tab].type = ITEM;
	hit_tab[calcul->index_hit_tab].side = calcul->side;
	calcul->index_hit_tab++;
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