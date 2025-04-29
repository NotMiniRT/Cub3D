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
	//printf("for teta: %f, height: %f\n", angle, res[0]);
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
	return (1);
}
// float R_H = 2 * tan(FOV * 0.5) / WINDOW_WIDTH;
// float R_V = 2 * tan(FOV * WINDOW_HEIGHT / (WINDOW_WIDTH * 0.5)) / WINDOW_HEIGHT;
// int intersect(int i, int j, int a , int b, int c, int d, float R_V, float R_H)
// {

// 	float ray[3];
	
// 	ray[0] = (i - WINDOW_WIDTH * 0.5) * R_V;
// 	ray[1] = -1;
// 	ray[2] = (WINDOW_HEIGHT * 0.5 - j) * R_H;
// 	printf("%d, %d: {ray: [%f, %f, %f], res: %f}\n", i, j, ray[0], ray[1], ray[2], a * ray[0] + b * ray [1] + c * ray[2] + d);
// 	if (a * ray[0] + b * ray [1] + c * ray[2] + d == 0)
// 		return (1);
// 	return (0);
// }