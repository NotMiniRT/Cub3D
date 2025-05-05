#include "main_struct.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "ray.h"

// int	get_color(t_image_cub *img, int x, int y, double height)
// {
// 	double step = 64.0f / height; // Combien de pixels de texture par pixel d'écran
// 	double texPos = (y - (WINDOW_HEIGHT / 2 - height / 2)) * step;

// 	int texY = (int)texPos;
// 	if (texY < 0) texY = 0;
// 	if (texY >= 64) texY = 63;

// 	int texX = (x * 64) / WINDOW_WIDTH;
// 	if (texX < 0) texX = 0;
// 	if (texX >= 64) texX = 63;

// 	int pixel = texY * img->line_bytes + texX * 4;

// 	unsigned char b = img->buffer[pixel + 0];
// 	unsigned char g = img->buffer[pixel + 1];
// 	unsigned char r = img->buffer[pixel + 2];
// 	unsigned char a = img->buffer[pixel + 3];
	
// 	return ((int)((a << 24) | (r << 16) | (g << 8) | b));
// }

// double wallX;
// if (res[1] == 0)
// 	wallX = row + res[0] * row;
// else
// 	wallX = j + res[0] * j;
// wallX -= floor(wallX);

int	get_color(t_image_cub *img, int texX, int texY)
{
	double pixel;

	pixel = (texY * img->line_bytes) + (texX * 4);

	unsigned char b = img->buffer[(int)pixel + 0];
	unsigned char g = img->buffer[(int)pixel + 1];
	unsigned char r = img->buffer[(int)pixel + 2];
	unsigned char a = img->buffer[(int)pixel + 3];
	
	return ((int)((a << 24) | (r << 16) | (g << 8) | b));
}

void render_one_ray(t_main_struct *main_struct, double teta_cos_sin[2], int row, double delta_teta, int i)
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
			change_pixel_color(main_struct->frame, 0x000000, row, j);
		else if (j > (WINDOW_HEIGHT + height) / 2)
			change_pixel_color(main_struct->frame, 0xFF0000, row, j);
		else if (res[1] == 1) {
			double wallX = main_struct->player->x + res[0] * teta_cos_sin[0];
			wallX -= floor(wallX);

			int texX = (int)(wallX * 64);
			if (texX < 0) texX = 0;
			if (texX >= 64) texX = 64 - 1;

			double step = (double)64 / height;
			double texPos = (j - (WINDOW_HEIGHT - height) / 2) * step;
			int texY = (int)texPos;

			if (texY < 0) texY = 0;
			if (texY >= 64) texY = 64 - 1;

			change_pixel_color(main_struct->frame, get_color(main_struct->wall, texX, texY), row, j);
			texPos += step;
		}
		else{
			double wallX = main_struct->player->y + res[0] * teta_cos_sin[1];
			wallX -= floor(wallX);

			int texX = (int)(wallX * 64);
			if (texX < 0) texX = 0;
			if (texX >= 64) texX = 64 - 1;

			double step = (double)64 / height;
			double texPos = (j - (WINDOW_HEIGHT - height) / 2) * step;
			int texY = (int)texPos;

			if (texY < 0) texY = 0;
			if (texY >= 64) texY = 64 - 1;

			change_pixel_color(main_struct->frame, get_color(main_struct->wall, texX, texY), row, j);
			texPos += step;}
		j++;
	}
}

int	frame_display(t_main_struct *main_struct)
{
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

	while(i < WINDOW_WIDTH)
	{
		render_one_ray(main_struct, teta_cos_sin, i, delta_teta, i);

		next_cos_teta = teta_cos_sin[0] * cos_delta - teta_cos_sin[1] * sin_delta;
		next_sin_teta = teta_cos_sin[1] * cos_delta + sin_delta * teta_cos_sin[0];
		teta_cos_sin[0] = next_cos_teta;
		teta_cos_sin[1] = next_sin_teta;

		i++;
	}
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, main_struct->frame->sprite, 0, 0);
	return (0);
}
