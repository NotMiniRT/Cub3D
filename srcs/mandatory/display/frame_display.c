#include "main_struct.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "ray.h"

void render_one_ray(t_main_struct *main_struct, double teta_cos_sin[2], t_image_cub *img, int row, double delta_teta, int i)
{
	int	j;
	double res[2];
	double height;
	res[0] = 0;
	res[1] = 0;

	ray_check(main_struct, &res, teta_cos_sin);

	height = (WINDOW_WIDTH / (1.154 * res[0] * cos(delta_teta * i - 0.5235988)));
	j = 0;
	while(j < WINDOW_HEIGHT)
	{
		if (j < (WINDOW_HEIGHT - height) / 2)
			change_pixel_color(img, 0x000000, row, j);
		else if (j > (WINDOW_HEIGHT + height) / 2)
			change_pixel_color(img, 0xFF0000, row, j);
		else if (res[1] == 1)
			change_pixel_color(img, 0x00FF00, row, j);
		else
			change_pixel_color(img, 0x0000FF, row, j);
		j++;
	}
}

int	frame_display(t_main_struct *main_struct)
{
	t_image_cub img;
	int i;

	double	teta;
	double	next_cos_teta;
	double	next_sin_teta;
	double  delta_teta;
	double	cos_delta;
	double	sin_delta;
	double teta_cos_sin[2];

	i = 0;
	delta_teta = FOVSWINDOW_WIDTH;
	teta = main_struct->player->fov_angle - 0.5235988;
	teta_cos_sin[0] = cos(teta);
	teta_cos_sin[1] = sin(teta);
	cos_delta = cos(delta_teta);
	sin_delta = sin(delta_teta);

	if (create_img(main_struct, &img))
		return (1);
	while(i < WINDOW_WIDTH)
	{
		render_one_ray(main_struct, teta_cos_sin, &img, i, delta_teta, i);

		next_cos_teta = teta_cos_sin[0] * cos_delta - teta_cos_sin[1] * sin_delta;
		next_sin_teta = teta_cos_sin[1] * cos_delta + sin_delta * teta_cos_sin[0];
		teta_cos_sin[0] = next_cos_teta;
		teta_cos_sin[1] = next_sin_teta;

		i++;
	}
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, img.sprite, 0, 0);
	mlx_destroy_image(main_struct->mlx_ptr, img.sprite);
	return (0);
}
