#include "structs.h"

int	get_color(t_image_cub *img, int texture_x, int texture_y)
{
	return (((int *)(img->buffer + (texture_y * img->line_bytes)
			+ (texture_x)))[0]);
}

void	change_pixel_color(t_image_cub *img, int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}
