#include "main_struct.h"
#include "common.h"
#include "player.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "ray.h"


void render_one_ray(t_main_struct *main_struct, double teta_cos_sin[2], int row, double teta)
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

	corrected_dist = res[0] * cos(teta - main_struct->player->fov_angle);
	height = (WINDOW_HEIGHT / corrected_dist);
	
	wall_hit_x = res[2] - floor(res[2]);
	if ((res[1] == 0 && teta_cos_sin[0] < 0)
		|| (res[1] == 1 && teta_cos_sin[1] > 0))
		wall_hit_x  = 1 - wall_hit_x ;
	text_x = 64. * wall_hit_x;
	if (text_x < 0) text_x = 0;
	if (text_x >= 64) text_x = 64 - 1;
	double step = (double)64. / height;
	double texPos = -(WINDOW_HEIGHT - height) / 2. * step;
	j = 0;	
	while(j < WINDOW_HEIGHT)
	{
		if ((row == WINDOW_WIDTH * 0.5) || j == (WINDOW_HEIGHT * 0.5))
			change_pixel_color(main_struct->frame, 0xFFFFFF, row, j);
		else if (j < (WINDOW_HEIGHT - height) / 2)
			change_pixel_color(main_struct->frame, 0x00AAAA, row, j);
		else if (j > (WINDOW_HEIGHT + height) / 2)
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
		texPos += step;
		j++;
	}
}

int	frame_display(t_main_struct *main_struct)
{
	int i;

	double	teta;
	// double	next_cos_teta;
	// double	next_sin_teta;
	//double  delta_x[3];
	// double	cos_delta;
	// double	sin_delta;
	double teta_cos_sin[2];

	i = 0;
	
	// 2 * i / camera - 1;


	double R_H =  2 * tan(FOV / 2) / WINDOW_WIDTH;
	
	while (i < WINDOW_WIDTH)
	{
		if (i < WINDOW_WIDTH * 0.5)
			teta = main_struct->player->fov_angle - atan(R_H * (WINDOW_WIDTH * 0.5 - i));
		else 
			teta = main_struct->player->fov_angle + atan(R_H * (i - WINDOW_WIDTH * 0.5));
		teta_cos_sin[0] = cos(teta);
		teta_cos_sin[1] = sin(teta);
		render_one_ray(main_struct, teta_cos_sin, i, teta);

		// next_cos_teta = teta_cos_sin[0] * cos_delta - teta_cos_sin[1] * sin_delta;
		// next_sin_teta = teta_cos_sin[1] * cos_delta + sin_delta * teta_cos_sin[0];
		// teta_cos_sin[0] = next_cos_teta;
		// teta_cos_sin[1] = next_sin_teta;

		i++;
	}
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, main_struct->frame->sprite, 0, 0);
	return (0);
}
