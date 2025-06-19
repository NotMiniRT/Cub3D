#include <math.h>

#include "common.h"
#include "player.h"
#include "ray.h"
#include "structs.h"

static inline void	change_pixel_color_opt(t_image_cub *img,
		int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}

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
	render_calc->text_y_index = -(WINDOW_HEIGHT - render_calc->height)
		* 0.5 * render_calc->step;
	render_calc->height_check_minus = (WINDOW_HEIGHT
			- render_calc->height) * 0.5;
	render_calc->height_check_plus = (WINDOW_HEIGHT
			+ render_calc->height) * 0.5;
	get_right_wall(render_calc, main_struct);
}

static void	render_on_screen(t_render_calculus *render_calc,
	t_main_struct *main_struct, int row, int j)
{
	if (j < render_calc->height_check_minus)
		change_pixel_color_opt(main_struct->frame, main_struct->ceil, row, j);
	else if (j > render_calc->height_check_plus)
		change_pixel_color_opt(main_struct->frame, main_struct->ground, row, j);
	else
	{
		render_calc->text_y = (int)render_calc->text_y_index;
		if (render_calc->text_y < 0)
			render_calc->text_y = 0;
		if (render_calc->text_y >= 64)
			render_calc->text_y = 64 - 1;
		change_pixel_color_opt(main_struct->frame,
			(render_calc->line_add + render_calc->text_y)[0], row, j);
	}
}

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
	ray_check(main_struct, &(render_calc.res), teta_cos_sin);
	get_calcul_param(&render_calc, main_struct, teta_cos_sin, row);
	row = row * 4;
	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		render_on_screen(&render_calc, main_struct, row, j);
		render_calc.text_y_index += render_calc.step;
		j = j + 1;
	}
}
