#include <math.h>
#include "common.h"
#include "doors_b.h"
#include "player_b.h"
#include "ray_b.h"
#include "libft.h"

static inline int	darken_color(int color, float factor)
{
	return (((int)(((color >> 16) & 0xFF) * factor) << 16) |
		((int)(((color >> 8) & 0xFF) * factor) << 8)
		| (int)(((color) & 0xFF) * factor));
}

static inline void	change_pixel_color_opt(t_image_cub *img,
		int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}

static void	render_on_screen(t_render_calculus *render_calc,
	t_main_struct *main_struct, int row, int j)
{
	if (j > render_calc->dark_height_check_plus)
		render_calc->floor_factor = render_calc->floor_factor * 0.98;
	if (put_transparency(render_calc, main_struct, row, j))
		return ;
	else if (j < render_calc->height_check_minus)
		change_pixel_color_opt(main_struct->frame,
			render_calc->ceil_factor, row, j);
	else if (j > render_calc->height_check_plus)
		change_pixel_color_opt(main_struct->frame,
			darken_color(main_struct->ground,
				1 - render_calc->floor_factor), row, j);
	else if (render_calc->res[3])
	{
		change_pixel_color_opt(main_struct->frame, 0, row, j);
	}
	else
	{
		render_calc->text_y = ((int)render_calc->text_y_index);
		if (render_calc->text_y < 0)
			render_calc->text_y = 0;
		change_pixel_color_opt(main_struct->frame,
			darken_color(render_calc->line_add[render_calc->text_y],
				render_calc->wall_factor), row, j);
	}
}

void	add_text_pos(t_render_calculus *render_calc)
{
	int	i;

	i = 0;
	render_calc->text_y_index += render_calc->step;
	while (i < render_calc->res[4])
	{
		render_calc->hit_tab[i].text_y_index += render_calc->hit_tab[i].step;
		i++;
	}
}

void	render_one_ray(t_main_struct *main_struct,
	double teta_cos_sin[2], int row, double teta)
{
	int					j;
	t_render_calculus	render_calc;

	j = -1;
	while (++j < 5)
		render_calc.res[j] = 0;
	render_calc.teta = teta;
	ray_check(main_struct, &(render_calc.res),
		teta_cos_sin, render_calc.hit_tab);
	get_calcul_param(&render_calc, main_struct, teta_cos_sin, row);
	if (render_calc.res[4] != 0)
		set_hit_tab(&render_calc, main_struct, row, teta_cos_sin);
	row = row * 4;
	render_calc.wall_factor = 1
		- (render_calc.res[0] / (main_struct->fuel * RENDER_DIST));
	render_calc.floor_factor = 1;
	render_calc.ceil_factor
		= darken_color(main_struct->ceil, main_struct->fuel - 0.05);
	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		render_on_screen(&render_calc, main_struct, row, j);
		add_text_pos(&render_calc);
	}
}
