#include "structs.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "minimap.h"

static void	minimap_set_pixel(t_image_cub *img, int x, int y, int color)
{
	char	*pixel;
	int		bytes_per_pixel;

	if (x < 0 || y < 0 || x >= (WINDOW_HEIGHT / 3) || y >= (WINDOW_HEIGHT / 3))
		return ;
	bytes_per_pixel = img->pixel_bits / 8;
	pixel = img->buffer + (y * img->line_bytes + x * bytes_per_pixel);
	if (img->endian == 0)
	{
		pixel[0] = (color) & 0xFF;
		pixel[1] = (color >> 8) & 0xFF;
		pixel[2] = (color >> 16) & 0xFF;
		pixel[3] = (color >> 24) & 0xFF;
	}
	else
	{
		pixel[0] = (color >> 24) & 0xFF;
		pixel[1] = (color >> 16) & 0xFF;
		pixel[2] = (color >> 8) & 0xFF;
		pixel[3] = (color) & 0xFF;
	}
}

void	draw_square(t_image_cub *img, int x, int y, int color)
{
	const int	block_size = (WINDOW_HEIGHT / 3) / (MINIMAP_RADIUS * 2);
	int			i;
	int			j;
	int			start_x;
	int			start_y;

	start_x = x * block_size;
	start_y = y * block_size;
	i = 0;
	while (i < block_size)
	{
		j = 0;
		while (j < block_size)
		{
			minimap_set_pixel(img, start_x + i, start_y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_image_cub *img)
{
	int		i;
	int		j;
	int		center_x;
	int		center_y;
	float	distance;

	center_x = (WINDOW_HEIGHT / 3) / 2;
	center_y = (WINDOW_HEIGHT / 3) / 2;
	i = -PLAYER_DOT_SIZE;
	while (i <= PLAYER_DOT_SIZE)
	{
		j = -PLAYER_DOT_SIZE;
		while (j <= PLAYER_DOT_SIZE)
		{
			distance = sqrt(i * i + j * j);
			if (distance <= PLAYER_DOT_SIZE)
				minimap_set_pixel(img, center_x + i, center_y + j, 0xFF2E86E1);
			j++;
		}
		i++;
	}
}

void	fill_minimap_background(t_image_cub *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < (WINDOW_HEIGHT / 3))
	{
		x = 0;
		while (x < (WINDOW_HEIGHT / 3))
		{
			minimap_set_pixel(img, x, y, 0x002E4053);
			x++;
		}
		y++;
	}
}
