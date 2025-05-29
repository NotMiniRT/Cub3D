#include "structs_b.h"

int	get_color(t_image_cub *img, int texture_x, int texture_y)
{
	int	offset;

	if (!img || !img->buffer)
		return (0);
	if (texture_x < 0 || texture_x >= img->width ||
		texture_y < 0 || texture_y >= img->height)
		return (0);
	offset = (texture_y * img->line_bytes) +
			(texture_x * (img->pixel_bits / 8));
	return (*(int *)(img->buffer + offset));
}

void	change_pixel_color(t_image_cub *img, int color, int x, int y)
{
	int	offset;

	if (!img || !img->buffer)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	offset = (y * img->line_bytes) + (x * (img->pixel_bits / 8));
	*(int *)(img->buffer + offset) = color;
}
