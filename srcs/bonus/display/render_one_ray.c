#include "common.h"
#include "structs_b.h"
#include "player_b.h"
#include "image_b.h"
#include "mlx.h"
#include <math.h>
#include "ray_b.h"
#include "libft.h"
#include "doors_b.h"
#include <stdio.h>
static inline void	change_pixel_color_opt(t_image_cub *img,
		int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}


/*
Obtient le mur a aficher en fonction du side et de la direction que face le joueur, si on ne fait absolument aucunne transcparence sur la porte il suffit de la remettre la
*/
static void	get_right_wall(t_render_calculus *render_calc,
	t_main_struct *main_struct)
{
	if (render_calc->res[3])
		render_calc->line_add = (int *)(main_struct->fog->buffer
				+ (render_calc->text_x * main_struct->fog->line_bytes));
	else if (is_facing_up(render_calc->teta) && render_calc->res[1] == 1)
		render_calc->line_add = (int *)(main_struct->wall_s->buffer
				+ (render_calc->text_x * main_struct->wall_s->line_bytes));
	else if (render_calc->res[1] == 1)
		render_calc->line_add = (int *)(main_struct->wall_n->buffer
				+ (render_calc->text_x * main_struct->wall_n->line_bytes));
	else if (is_facing_left(render_calc->teta))
		render_calc->line_add = (int *)(main_struct->wall_e->buffer
				+ (render_calc->text_x * main_struct->wall_e->line_bytes));
	else
		render_calc->line_add = (int *)(main_struct->wall_o->buffer
				+ (render_calc->text_x * main_struct->wall_o->line_bytes));
}

/*
height: taille en pixel a l'ecran corrigee
wall_pc: point de collision avec le mur, en %
step: avancee en y sur l'ecrn pour chaque iteration ( pour les murs)
text_x/y: la position en x/y sur la texture
texpos: point de depart du mur en y
height_check_minus?max: debut et fin du mur en y
*/
static void	get_calcul_param(t_render_calculus *render_calc,
	t_main_struct *main_struct, double teta_cos_sin[2], int row)
{
	render_calc->height = (WINDOW_HEIGHT
			/ (render_calc->res[0] * main_struct->cos_r_h_tab[row]));
	if (render_calc->res[3])
		render_calc->text_x = fmod((0.21 * row), 64);
	else
	{
		render_calc->wall_pc = render_calc->res[2] - floor(render_calc->res[2]);
		if ((render_calc->res[1] == 0 && teta_cos_sin[0] < 0)
			|| (render_calc->res[1] == 1 && teta_cos_sin[1] > 0))
			render_calc->wall_pc = 1 - render_calc->wall_pc;
		render_calc->text_x = 64. * render_calc->wall_pc;
		if (render_calc->text_x < 0)
			render_calc->text_x = 0;
		if (render_calc->text_x >= 64)
			render_calc->text_x = 64 - 1;
	}
	render_calc->step = 64. / render_calc->height;
	render_calc->texpos = -(WINDOW_HEIGHT - render_calc->height)
		* 0.5 * render_calc->step;
	render_calc->height_check_minus = (WINDOW_HEIGHT
			- render_calc->height) * 0.5;
	render_calc->height_check_plus = (WINDOW_HEIGHT
			+ render_calc->height) * 0.5;
	get_right_wall(render_calc, main_struct);
}


/*
boucle sur le tableau de collision pour chaque pixel du rayon et verfie si il y a besoin de l'afficher
la partie commentee sert a reccuperer le bon pixel, il faut remplacer text_y/x par les coordonnes a reccuperer sur la texture
*/
int	put_transparency(t_render_calculus *render_calc,
	t_main_struct *main_struct, int row, int j)
{
	int i;
	int color;
	int text_y;

	i = 0;
	while(i <= 9 && render_calc->hit_tab[i].type != NOTHING)
	{
		// printf("max: %d, minus: %d, j = %d, status: %d\n", render_calc->hit_tab[i].height_check_plus, render_calc->hit_tab[i].height_check_minus, j, render_calc->hit_tab[i].status);
		if (render_calc->hit_tab[i].status != 0 && j < render_calc->hit_tab[i].height_check_plus && j > render_calc->hit_tab[i].height_check_minus)
		{
			text_y = (int)render_calc->hit_tab[i].texpos;
			if (text_y < 0)
				text_y = 0;
			color = (render_calc->hit_tab[i].line_add + text_y)[0];
			if (color != 0)
			{
				change_pixel_color_opt(main_struct->frame, color, row, j);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

/*
pLACE LA COULEUR DU PIXEL si aucunne collision n'a eu besoin de s'afficher
*/
static void	render_on_screen(t_render_calculus *render_calc,
	t_main_struct *main_struct, int row, int j)
{

	if (put_transparency(render_calc, main_struct, row, j))
		return ;
	else if (j < render_calc->height_check_minus)
		change_pixel_color_opt(main_struct->frame, main_struct->ceil, row, j);
	else if (j > render_calc->height_check_plus)
		change_pixel_color_opt(main_struct->frame, main_struct->ground, row, j);
	else
	{
		render_calc->text_y = ((int)render_calc->texpos);
		if (render_calc->text_y < 0)
			render_calc->text_y  = 0;
		change_pixel_color_opt(main_struct->frame,
			render_calc->line_add[render_calc->text_y], row, j);
	}
}

/*
effectue les clculs de base pour chaque eleemnt du tableau de colision
*/
void set_hit_tab(t_render_calculus *render_calc, t_main_struct *main_struct, int row, double teta_cos_sin[2])
{
	int i;

	i = 0;
	while(i <= 9 && render_calc->hit_tab[i].type != NOTHING)
	{
		if (render_calc->hit_tab[i].type == DOOR)
		{
			render_calc->hit_tab[i].status = get_status_door(render_calc->hit_tab[i].map_x, render_calc->hit_tab[i].map_y, main_struct);
			render_calc->hit_tab[i].height = (WINDOW_HEIGHT
					/ (render_calc->hit_tab[i].dist * main_struct->cos_r_h_tab[row]));

			if ((render_calc->hit_tab[i].side == 0 && teta_cos_sin[0] < 0)
				|| (render_calc->hit_tab[i].side == 1 && teta_cos_sin[1] > 0))
				render_calc->hit_tab[i].wall_pc  = 1 - render_calc->hit_tab[i].wall_pc ;
			render_calc->hit_tab[i].text_x = 64. * render_calc->hit_tab[i].wall_pc ;
			if (render_calc->hit_tab[i].text_x < 0)
				render_calc->hit_tab[i].text_x = 0;
			if (render_calc->hit_tab[i].text_x >= 64)
				render_calc->hit_tab[i].text_x = 64 - 1;
			render_calc->hit_tab[i].step = 64. / render_calc->hit_tab[i].height;
			render_calc->hit_tab[i].texpos = -(WINDOW_HEIGHT - render_calc->hit_tab[i].height)
				* 0.5 * render_calc->hit_tab[i].step;
			render_calc->hit_tab[i].height_check_minus = (WINDOW_HEIGHT
					- render_calc->hit_tab[i].height) * 0.5;
			render_calc->hit_tab[i].height_check_plus = (WINDOW_HEIGHT
					+ render_calc->hit_tab[i].height) * 0.5;

			render_calc->hit_tab[i].line_add = (int *)(main_struct->door->buffer
				+ (render_calc->hit_tab[i].text_x * main_struct->door->line_bytes));
			i++;
		}
		else if (render_calc->hit_tab[i].type == ITEM)
		{
			render_calc->hit_tab[i].height = (WINDOW_HEIGHT
				/ (render_calc->hit_tab[i].dist * main_struct->cos_r_h_tab[row]));
			render_calc->hit_tab[i].text_x = 64. * render_calc->hit_tab[i].wall_pc;
			if (render_calc->hit_tab[i].text_x < 0)
				render_calc->hit_tab[i].text_x = 0;
			if (render_calc->hit_tab[i].text_x >= 64)
				render_calc->hit_tab[i].text_x = 64 - 1;
			render_calc->hit_tab[i].step = 64. / render_calc->hit_tab[i].height;
			render_calc->hit_tab[i].texpos = -(WINDOW_HEIGHT - render_calc->hit_tab[i].height)
					* 0.5 * render_calc->hit_tab[i].step;
			render_calc->hit_tab[i].height_check_minus = (WINDOW_HEIGHT
					- render_calc->hit_tab[i].height) * 0.5;
			render_calc->hit_tab[i].height_check_plus = (WINDOW_HEIGHT
					+ render_calc->hit_tab[i].height) * 0.5;
			render_calc->hit_tab[i].line_add = (int *)(main_struct->potion->buffer
				+ (render_calc->hit_tab[i].text_x * main_struct->potion->line_bytes));
			render_calc->hit_tab[i].status = 1;
			i++;
		}
	}
}
/*
beta: servirait a incrementer tout les textpos, items et murs, potentiellement inutile
*/
void add_text_pos(t_render_calculus *render_calc)
{
	int i;

	i = 0;
	render_calc->texpos += render_calc->step;
	while (i <= 9 && render_calc->hit_tab[i].type != NOTHING)
	{
		render_calc->hit_tab[i].texpos += render_calc->hit_tab[i].step;
		i++;
	}
}	
/*
recupere les donnees du rayonpuis boucle sur tout les pixels de la rangee
*/
void	render_one_ray(t_main_struct *main_struct,
	double teta_cos_sin[2], int row, double teta)
{
	int					j;
	t_render_calculus	render_calc;

	render_calc.res[0] = 0;
	render_calc.res[1] = 0;
	render_calc.res[2] = 0;
	render_calc.res[3] = 0;
	render_calc.teta = teta;
	ft_bzero(render_calc.hit_tab, 10 * sizeof(t_object_hit));
	ray_check(main_struct, &(render_calc.res), teta_cos_sin, render_calc.hit_tab);
	get_calcul_param(&render_calc, main_struct, teta_cos_sin, row);
	if (render_calc.hit_tab[0].type != NOTHING)
		set_hit_tab(&render_calc, main_struct, row, teta_cos_sin);
	row = row * 4;
	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		render_on_screen(&render_calc, main_struct, row, j);
		add_text_pos(&render_calc);
		j = j + 1;
	}
}
