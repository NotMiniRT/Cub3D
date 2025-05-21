#include "structs_b.h"
#include "math.h"
#include "common.h"
/*
reccupere les parametres pour les rayons,
	dir_x/y: les omposantes pour la direction, cos et sin
	delta_y/x: la distances entre les murs verticux/horizontaux suivant l'axe du rayon
*/
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
		calcul->delta_x = 10000000;
	else
		calcul->delta_x = fabs(1.0 / calcul->dir_x);
	if (fabs(calcul->dir_y) < 0.000001)
		calcul->delta_y = 10000000;
	else
		calcul->delta_y = fabs(1.0 / calcul->dir_y);
	calcul->index_hit_tab = 0;
}

/*
reccupere les parametres pour les rayons,
	step: permet de se deplacer dans le bon sens a l'interieur
	side: utis pour les murs, connaitre de quel cote on les frappe avec le rayon
*/
static void	get_step_and_side_dist(t_ray_calculus *calcul)
{
	if (calcul->dir_x < 0)
	{
		calcul->step_x = -1;
		calcul->side_dist_x = (calcul->player_x - calcul->map_x)
			* calcul->delta_x;
	}
	else
	{
		calcul->step_x = 1;
		calcul->side_dist_x = (calcul->map_x + 1.0 - calcul->player_x)
			* calcul->delta_x;
	}
	if (calcul->dir_y < 0)
	{
		calcul->step_y = -1;
		calcul->side_dist_y = (calcul->player_y - calcul->map_y)
			* calcul->delta_y;
	}
	else
	{
		calcul->step_y = 1;
		calcul->side_dist_y = (calcul->map_y + 1.0 - calcul->player_y)
			* calcul->delta_y;
	}
	calcul->side = 0;
}
/*
calcul de la distance avec le mur ainsi que les coorodonnes
*/
static void	get_dists_and_wall_x_y(t_ray_calculus *calcul)
{
	if (calcul->side == 0)
	{
		calcul->wall_x = (calcul->map_x - calcul->player_x
				+ (1 - calcul->step_x) * 0.5);
		calcul->wall_y = ((calcul->map_x - calcul->player_x
					+ (1 - calcul->step_x) * 0.5)
				/ calcul->dir_x) * calcul->dir_y;
		calcul->dist = calcul->side_dist_x - calcul->delta_x;
	}
	else
	{
		calcul->wall_x = ((calcul->map_y - calcul->player_y
					+ (1 - calcul->step_y) * 0.5)
				/ calcul->dir_y) * calcul->dir_x;
		calcul->wall_y = (calcul->map_y - calcul->player_y
				+ (1 - calcul->step_y) * 0.5);
		calcul->dist = calcul->side_dist_y - calcul->delta_y;
	}
}
/*
repmlis les resultats:
	0-> la distance;
	1-> le side;
	2-> le %du mur a l'imapct, sert pour calculer quelle colone afficher
*/
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

/*
reccupere les collisions et leur donnee, il faudra peut etre en rajouter (pareil, il faut verifier qu'une porte soit active avant de l'ajouer pour eviter les calculs inutiles)
*/
void	add_hit_ray(t_ray_calculus *calcul, t_object_hit	hit_tab[10])
{
	if (calcul->index_hit_tab >= 10)
		return ;

	if (calcul->side == 0)
	{
		hit_tab[calcul->index_hit_tab].wall_pc = calcul->player_y + ((calcul->map_x - calcul->player_x
					+ (1 - calcul->step_x) * 0.5)
				/ calcul->dir_x) * calcul->dir_y;
		hit_tab[calcul->index_hit_tab].dist = calcul->side_dist_x + calcul->delta_x;
	}
	else
	{
		hit_tab[calcul->index_hit_tab].wall_pc = calcul->player_x + ((calcul->map_y - calcul->player_y
					+ (1 - calcul->step_y) * 0.5)
				/ calcul->dir_y) * calcul->dir_x;
		hit_tab[calcul->index_hit_tab].dist = calcul->side_dist_y + calcul->delta_y;
	}

	hit_tab[calcul->index_hit_tab].map_x = (int)calcul->map_y;
	hit_tab[calcul->index_hit_tab].map_y = (int)calcul->map_x;
	hit_tab[calcul->index_hit_tab].type = DOOR;
	hit_tab[calcul->index_hit_tab].side = calcul->side;
	calcul->index_hit_tab++;
}
/*
boucle principale, avance sur l'axe du rayon en x/y en fonction de la distance la plus petite parcourue sur les axes respectifs, jusqua la premiere collision avec un mur, puis renvoie les resultats
*/
void	ray_check(t_main_struct *main_struct,
		double (*cross)[4], double cos_sin[2], t_object_hit	hit_tab[10])
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
		if (main_struct->map[calcul.map_y][calcul.map_x] == 'D')
			add_hit_ray(&calcul, hit_tab);
		if (calcul.side_dist_x < calcul.side_dist_y)
		{
			calcul.side_dist_x += calcul.delta_x;
			calcul.map_x += calcul.step_x;
			calcul.side = 0;
		}
		else
		{
			calcul.side_dist_y += calcul.delta_y;
			calcul.map_y += calcul.step_y;
			calcul.side = 1;
		}
	}
	get_dists_and_wall_x_y(&calcul);
	fill_cross(&calcul, cross);
}
