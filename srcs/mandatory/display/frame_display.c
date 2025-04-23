#include "main_struct.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

int	frame_display(t_main_struct *main_struct)
{
	t_image_cub img;

	if (create_img(main_struct, &img))
	return (1);
	for(int i = 0; i < WINDOW_HEIGHT; ++i)
	for(int j = 0; j < WINDOW_WIDTH; ++j)
	{
		change_pixel_color(&img, 0x000000, j, i);
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