#include "main_struct.h"
#include "common.h"
#include "player.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "ray.h"

// double max(double a, double b) {
//     return (a > b) ? a : b;
// }

// double min(double a, double b) {
//     return (a < b) ? a : b;
// }

// void	add_pixel_color(t_image_cub *img, double dist, int x, int y, char is_not_wall)
// {
// 	int pixel;
// 	double t_normalized;
// 	double j_mapping;

// 	j_mapping = 1;
// 	t_normalized = 1 - max(0.0, min(1.0, (dist - 2.0) / 3.0));
// 	// printf("%f\n", t_normalized);
// 	pixel = (y * img->line_bytes) + (x * 4);

// 	if (is_not_wall)
// 		j_mapping = fabs(max(0, min(1080, y)) - 540) / 540;
// 	img->buffer[pixel + 0] = (unsigned char)img->buffer[pixel + 0] * (t_normalized * j_mapping);
// 	img->buffer[pixel + 1] = (unsigned char)img->buffer[pixel + 1] * (t_normalized * j_mapping);
// 	img->buffer[pixel + 2] = (unsigned char)img->buffer[pixel + 2] * (t_normalized * j_mapping);
// 	// if (img->buffer[pixel + 0] > 200)
// 	// {
// 	// 	printf("%f \n", t_normalized);
// 	// }
// }

static inline int	get_color(t_image_cub *img, int texture_x, int texture_y)
{
	return (((int *)(img->buffer + (texture_y * img->line_bytes) + (texture_x)))[0]);
}

static inline void	change_pixel_color(t_image_cub *img, int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}

void render_one_ray(t_main_struct *main_struct, double teta_cos_sin[2], int row)
{
	int	j;
	double res[3];
	double height;
	double corrected_dist;
	double wall_hit_x;
	int text_x;
	int text_y;
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	ray_check(main_struct, &res, teta_cos_sin);

	corrected_dist = res[0] * main_struct->cos_R_H_tab[row];
	height = (WINDOW_HEIGHT / corrected_dist);
	
	wall_hit_x = res[2] - floor(res[2]);
	if ((res[1] == 0 && teta_cos_sin[0] < 0)
		|| (res[1] == 1 && teta_cos_sin[1] > 0))
		wall_hit_x  = 1 - wall_hit_x ;
	text_x = 64. * wall_hit_x;
	if (text_x < 0) text_x = 0;
	if (text_x >= 64) text_x = 64 - 1;
	double step = (double)64. / height;
	double texPos = -(WINDOW_HEIGHT - height) * 0.5 * step;
	int height_check_minus = (WINDOW_HEIGHT - height) * 0.5;
	int height_check_plus = (WINDOW_HEIGHT + height) * 0.5;
	
	text_x = text_x * 4;
	row = row * 4;
	j = 0;	
	while(j < WINDOW_HEIGHT)
	{
		if (j < height_check_minus)
			change_pixel_color(main_struct->frame, 0x00AAAA, row, j);
		else if (j > height_check_plus)
			change_pixel_color(main_struct->frame, 0xAAAA00, row, j);
		else if (res[1] == 1) {

			text_y = (int)texPos;

			if (text_y < 0) text_y = 0;
			if (text_y >= 64) text_y = 64 - 1;

			change_pixel_color(main_struct->frame, get_color(main_struct->wall, text_x, text_y), row, j);
		}
		else{
			text_y = (int)texPos;

			if (text_y < 0) text_y = 0;
			if (text_y >= 64) text_y = 64 - 1;

			change_pixel_color(main_struct->frame, get_color(main_struct->wall, text_x, text_y), row, j);
		}

		// if (corrected_dist > 2)
		// 	add_pixel_color(main_struct->frame, corrected_dist, row, j, (j < (WINDOW_HEIGHT - height) / 2 || j > (WINDOW_HEIGHT + height) / 2));
		texPos += step;
		j = j + 1;
	}
}

int	frame_display(t_main_struct *main_struct)
{
	int row;

	double teta;
	double teta_cos_sin[2];

	row = 0;
	while (row < WINDOW_WIDTH)
	{

		teta = main_struct->player->fov_angle + main_struct->R_H_tab[row];
		teta_cos_sin[0] = cos(teta);
		teta_cos_sin[1] = sin(teta);
		render_one_ray(main_struct, teta_cos_sin, row);
		row++;
	}
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, main_struct->frame->sprite, 0, 0);
	return (0);
}
