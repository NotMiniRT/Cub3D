#include "image.h"
#include "common.h"
#include "main_struct.h"
#include "mlx.h"
#include <stdlib.h>

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