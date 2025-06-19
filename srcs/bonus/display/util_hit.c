#include <math.h>

#include "structs_b.h"

t_point	calcul_intersection(t_point p1,
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

double	dist_points(t_point a, t_point b)
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