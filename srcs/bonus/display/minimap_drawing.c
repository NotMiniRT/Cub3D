#include "structs_b.h"
#include "common.h"
#include "image_b.h"
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

	if (x < 0 || y < 0 || x >= (WINDOW_HEIGHT * 0.333) || y >= (WINDOW_HEIGHT * 0.333))
		return ;
	bytes_per_pixel = img->pixel_bits * 0.125;
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

void	draw_square_with_offset(t_image_cub *img, t_minimap *minimap)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = minimap->x * minimap->block_size + -minimap->offset_x;
	start_y = minimap->y * minimap->block_size + -minimap->offset_y;
	i = 0;
	while (i < minimap->block_size)
	{
		j = 0;
		while (j < minimap->block_size)
		{
			if (start_x + i >= 0 && start_x + i < (WINDOW_HEIGHT * 0.333) && \
				start_y + j >= 0 && start_y + j < (WINDOW_HEIGHT * 0.333))
				minimap_set_pixel(img, \
									start_x + i, start_y + j, minimap->color);
			j++;
		}
		i++;
	}
}

static void	draw_player_dot(t_image_cub *img, t_minimap_player *player)
{
	while (player->i <= PLAYER_DOT_SIZE)
	{
		player->j = -PLAYER_DOT_SIZE;
		while (player->j <= PLAYER_DOT_SIZE)
		{
			player->distance = \
							sqrt(player->i * player->i + player->j * player->j);
			if (player->distance <= PLAYER_DOT_SIZE)
				minimap_set_pixel(img, player->center_x + player->i, \
					player->center_y + player->j, 0xFF2E86E1);
			player->j++;
		}
		player->i++;
	}
}

void	draw_player(t_image_cub *img, double angle)
{
	t_minimap_player	player;

	player.center_x = (WINDOW_HEIGHT * 0.333) * 0.5;
	player.center_y = (WINDOW_HEIGHT * 0.333) * 0.5;
	player.i = -PLAYER_DOT_SIZE;
	draw_player_dot(img, &player);
	player.dir_x = cos(angle) * (PLAYER_DOT_SIZE * 2);
	player.dir_y = sin(angle) * (PLAYER_DOT_SIZE * 2);
	player.i = 0;
	while (player.i <= PLAYER_DOT_SIZE * 2)
	{
		minimap_set_pixel(img,
			player.center_x + (player.dir_x * player.i) / (PLAYER_DOT_SIZE * 2),
			player.center_y + (player.dir_y * player.i) / (PLAYER_DOT_SIZE * 2),
			0xFFFFFFFF);
		player.i++;
	}
}

void	fill_minimap_background(t_image_cub *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < (WINDOW_HEIGHT * 0.333))
	{
		x = 0;
		while (x < (WINDOW_HEIGHT * 0.333))
		{
			minimap_set_pixel(img, x, y, 0x00101825);
			x++;
		}
		y++;
	}
}
