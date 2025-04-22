#include <stdlib.h>
#include "inputs.h"
#include "main_struct.h"
#include "mlx.h"
#include "common.h"
#include "image.h"

void	change_pixel_color(t_image_cub *img, int color, int x, int y)
{
	int pixel;
	
	pixel = (y * img->line_bytes) + (x * 4);

	img->buffer[pixel + 0] = (color) & 0xFF;
	img->buffer[pixel + 1] = (color >> 8) & 0xFF;
	img->buffer[pixel + 2] = (color >> 16) & 0xFF;
	img->buffer[pixel + 3] = (color >> 24);
}

int create_img(t_main_struct *main_struct, t_image_cub *img)
{
	img->sprite = mlx_new_image(main_struct->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img->sprite == NULL)
		return (1);
	img->buffer = mlx_get_data_addr(img->sprite, &(img->pixel_bits), &(img->line_bytes), &(img->endian));
	if (img->buffer == NULL)
	{
		mlx_destroy_image(main_struct->mlx_ptr, img->sprite);
		return(1);
	}
	return (0);
}

int	frame_display(t_main_struct *main_struct)
{
	t_image_cub img;
	
	if (create_img(main_struct, &img))
		return (1);
	int j = 0;
	int color = 0x0;
	for(int y = 0; y < WINDOW_HEIGHT; ++y)
		for(int x = 0; x < WINDOW_WIDTH; ++x)
		{
			j++;
			if (j%3 == 0)
				color = 0xFF0000;
			if (j%3 == 1)
				color = 0x00FF00;
			if (j%3 == 2)
				color = 0x0000FF;
			change_pixel_color(&img, color, x, y);
		}
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, img.sprite, 0, 0);
	mlx_destroy_image(main_struct->mlx_ptr, img.sprite);
	return (1);
}

static int	init_display(t_main_struct *main_struct)
{
	main_struct->mlx_ptr = mlx_init();
	if (main_struct->mlx_ptr == NULL)
		return (1);
	main_struct->win_ptr = mlx_new_window(main_struct->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (main_struct->mlx_ptr == NULL)
		return (1);
	return (0);
}

static void	init_inputs(t_main_struct *main_struct)
{
	mlx_do_key_autorepeatoff(main_struct->mlx_ptr);
	mlx_loop_hook(main_struct->mlx_ptr, frame_display, main_struct);
	mlx_hook(main_struct->win_ptr, 3, 1L << 1, handle_input, main_struct);
	mlx_hook(main_struct->win_ptr, 17, 1, on_destroy, main_struct);
}

int	start_display(t_main_struct *main_struct)
{
	if (init_display(main_struct))
		return (1);
	init_inputs(main_struct);
	mlx_loop(main_struct->mlx_ptr);
	mlx_do_key_autorepeaton(main_struct->mlx_ptr);
	return (0);
}

