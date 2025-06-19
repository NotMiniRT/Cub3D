#include <math.h>

#include "common.h"
#include "structs_b.h"
#include "player_b.h"

static double	get_right_size(t_render_calculus *render_calc,
	t_main_struct *main_struct)
{
	if (is_facing_up(render_calc->teta) && render_calc->res[1] == 1)
		return (main_struct->wall_s->size);
	else if (render_calc->res[1] == 1)
		return (main_struct->wall_n->size);
	else if (is_facing_left(render_calc->teta))
		return (main_struct->wall_e->size);
	return (main_struct->wall_o->size);
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

static int	calcul_fog(t_render_calculus *render_calc,
	t_main_struct *main_struct, int row)
{
	render_calc->dark_height = (WINDOW_HEIGHT
			/ ((main_struct->fuel * RENDER_DIST)
				* main_struct->cos_r_h_tab[row]));
	render_calc->dark_height_check_minus = (WINDOW_HEIGHT
			- render_calc->dark_height) * 0.5;
	render_calc->dark_height_check_plus = (WINDOW_HEIGHT
			+ render_calc->dark_height) * 0.5;
	if (render_calc->res[3])
	{
		render_calc->height = render_calc->dark_height;
		render_calc->height_check_minus = render_calc->dark_height_check_minus;
		render_calc->height_check_plus = render_calc->dark_height_check_plus;
		return (1);
	}
	return (0);
}

void	get_calcul_param(t_render_calculus *render_calc,
	t_main_struct *main_struct, double teta_cos_sin[2], int row)
{
	double	size;

	if (calcul_fog(render_calc, main_struct, row))
		return ;
	render_calc->height = (WINDOW_HEIGHT
			/ (render_calc->res[0] * main_struct->cos_r_h_tab[row]));
	size = get_right_size(render_calc, main_struct);
	render_calc->wall_pc = render_calc->res[2] - floor(render_calc->res[2]);
	if ((render_calc->res[1] == 0 && teta_cos_sin[0] < 0)
		|| (render_calc->res[1] == 1 && teta_cos_sin[1] > 0))
		render_calc->wall_pc = 1 - render_calc->wall_pc;
	render_calc->text_x = size * render_calc->wall_pc;
	if (render_calc->text_x < 0)
		render_calc->text_x = 0;
	if (render_calc->text_x >= size)
		render_calc->text_x = size - 1;
	render_calc->step = size / render_calc->height;
	render_calc->text_y_index = -(WINDOW_HEIGHT - render_calc->height)
		* 0.5 * render_calc->step;
	render_calc->height_check_minus = (WINDOW_HEIGHT
			- render_calc->height) * 0.5;
	render_calc->height_check_plus = (WINDOW_HEIGHT
			+ render_calc->height) * 0.5;
	get_right_wall(render_calc, main_struct);
}
