#include "main_struct.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "ray.h"

void render_one_ray(t_main_struct *main_struct, float angle, t_image_cub *img, int row)
{
	int	j;
	float res[2];
	float height;
	res[0] = 0;
	res[1] = 0;
	ray_check(main_struct, &res, angle);

	height = (WINDOW_WIDTH / (1.154 * res[0])) / cos(angle - main_struct->player->fov_angle);
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
	float	teta;
	float   delta_teta;
	i = 0;
	delta_teta = FOV / WINDOW_WIDTH;
	teta = main_struct->player->fov_angle - 0.5235988;
	if (create_img(main_struct, &img))
		return (1);
	while(i < WINDOW_WIDTH)
	{
		teta = teta + delta_teta;
		render_one_ray(main_struct, teta, &img, i);
		i++;
	}
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, img.sprite, 0, 0);
	mlx_destroy_image(main_struct->mlx_ptr, img.sprite);
	return (0);
}
