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

static t_image_cub	*get_texture_for_wall(t_render_calculus *rc,
		t_main_struct *ms, double teta_cos_sin[2])
{
	if (rc->res[3])
		return (ms->fog);

	// For horizontal walls (rc->res[1] == 1)
	if (rc->res[1] == 1)
	{
		// Check if ray is going up (sin < 0) or down (sin > 0)
		if (teta_cos_sin[1] < 0)  // Ray going up, hits bottom of wall
			return (ms->wall_n);   // North wall texture
		else                       // Ray going down, hits top of wall
			return (ms->wall_s);   // South wall texture
	}
	else  // For vertical walls (rc->res[1] == 0)
	{
		// Check if ray is going left (cos < 0) or right (cos > 0)
		if (teta_cos_sin[0] < 0)   // Ray going left, hits right side of wall
			return (ms->wall_e);    // East wall texture
		else                        // Ray going right, hits left side of wall
			return (ms->wall_o);    // West wall texture
	}
}

static void	get_right_wall(t_render_calculus *rc, t_main_struct *ms,
		double teta_cos_sin[2])
{
	t_image_cub	*texture;

	texture = get_texture_for_wall(rc, ms, teta_cos_sin);
	rc->current_texture = texture;
	rc->line_add = (int *)(texture->buffer
			+ (rc->text_x * texture->line_bytes));
}

static void	calculate_texture_coords(t_render_calculus *rc,
		double teta_cos_sin[2], int row, t_main_struct *ms)
{
	t_image_cub	*texture;

	texture = get_texture_for_wall(rc, ms, teta_cos_sin);
	if (rc->res[3])
		rc->text_x = fmod((0.21 * row), texture->width);
	else
	{
		rc->wall_pc = rc->res[2] - floor(rc->res[2]);
		if ((rc->res[1] == 0 && teta_cos_sin[0] < 0)
			|| (rc->res[1] == 1 && teta_cos_sin[1] > 0))
			rc->wall_pc = 1 - rc->wall_pc;
		rc->text_x = texture->width * rc->wall_pc;
		if (rc->text_x < 0)
			rc->text_x = 0;
		if (rc->text_x >= texture->width)
			rc->text_x = texture->width - 1;
	}
}

static void	get_calcul_param(t_render_calculus *rc,
		t_main_struct *ms, double teta_cos_sin[2], int row)
{
	t_image_cub	*texture;

	rc->height = (WINDOW_HEIGHT
			/ (rc->res[0] * ms->cos_r_h_tab[row]));
	calculate_texture_coords(rc, teta_cos_sin, row, ms);
	texture = get_texture_for_wall(rc, ms, teta_cos_sin);
	rc->step = (double)texture->height / rc->height;
	rc->texpos = -(WINDOW_HEIGHT - rc->height)
		* 0.5 * rc->step;
	rc->height_check_minus = (WINDOW_HEIGHT
			- rc->height) * 0.5;
	rc->height_check_plus = (WINDOW_HEIGHT
			+ rc->height) * 0.5;
	get_right_wall(rc, ms, teta_cos_sin);
}

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
/**
 * @brief valeurs set a 2048 pour l'instant parce que joue avec les portes mais on va devoir changer ca aussi
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
			render_calc->hit_tab[i].text_x = 2048. * render_calc->hit_tab[i].wall_pc ;
			if (render_calc->hit_tab[i].text_x < 0)
				render_calc->hit_tab[i].text_x = 0;
			if (render_calc->hit_tab[i].text_x >= 2048)
				render_calc->hit_tab[i].text_x = 2048 - 1;
			render_calc->hit_tab[i].step = 2048. / render_calc->hit_tab[i].height;
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

static void	render_on_screen(t_render_calculus *rc,
		t_main_struct *ms, int row, int j)
{
	if (put_transparency(rc, ms, row, j))
		return ;
	if (j < rc->height_check_minus)
		change_pixel_color_opt(ms->frame, ms->ceil, row, j);
	else if (j > rc->height_check_plus)
		change_pixel_color_opt(ms->frame, ms->ground, row, j);
	else
	{
		rc->text_y = (int)rc->texpos;
		if (rc->text_y < 0)
			rc->text_y = 0;
		if (rc->text_y >= rc->current_texture->height)
			rc->text_y = rc->current_texture->height - 1;
		change_pixel_color_opt(ms->frame,
			(rc->line_add + rc->text_y)[0], row, j);
	}
}

void	render_one_ray(t_main_struct *ms,
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

	ray_check(ms, &(render_calc.res), teta_cos_sin, render_calc.hit_tab);
	get_calcul_param(&render_calc, ms, teta_cos_sin, row);
	if (render_calc.hit_tab[0].type != NOTHING)
		set_hit_tab(&render_calc, ms, row, teta_cos_sin);
	row = row * 4;
	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		render_on_screen(&render_calc, ms, row, j);
		add_text_pos(&render_calc);
		j = j + 1;
	}
}
