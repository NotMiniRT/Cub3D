#include "structs.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "minimap.h"

/* Debug pour vérifier les dimensions et caractéristiques de l'image
static void	debug_image_size(t_main_struct *main_struct)
{
	if (main_struct->minimap)
	{
		printf("Minimap info:\n");
		printf("- MINIMAP_SIZE: %d pixels\n", MINIMAP_SIZE);
		printf("- BLOCK_SIZE: %d pixels\n", BLOCK_SIZE);
		printf("- Image pointer: %p\n", main_struct->minimap->sprite);
		printf("- Buffer pointer: %p\n", main_struct->minimap->buffer);
		printf("- Pixel bits: %d\n", main_struct->minimap->pixel_bits);
		printf("- Line bytes: %d\n", main_struct->minimap->line_bytes);
		printf("- Endian: %d\n", main_struct->minimap->endian);
	}
	else
	{
		printf("Minimap is NULL\n");
	}
}

// Test qui dessine un carré et des diagonales pour vérifier la zone utilisable
static void	test_fill_entire_image(t_image_cub *img)
{
	int	x;
	int	y;

	// Remplir le fond en noir
	for (y = 0; y < MINIMAP_SIZE; y++)
	{
		for (x = 0; x < MINIMAP_SIZE; x++)
		{
			minimap_set_pixel(img, x, y, 0x000000FF);
		}
	}

	// Dessiner un cadre rouge
	for (x = 0; x < MINIMAP_SIZE; x++)
	{
		minimap_set_pixel(img, x, 0, 0xFF0000FF);               // Ligne du haut
		minimap_set_pixel(img, x, MINIMAP_SIZE - 1, 0xFF0000FF); // Ligne du bas
	}

	for (y = 0; y < MINIMAP_SIZE; y++)
	{
		minimap_set_pixel(img, 0, y, 0xFF0000FF);               // Ligne de gauche
		minimap_set_pixel(img, MINIMAP_SIZE - 1, y, 0xFF0000FF); // Ligne de droite
	}

	// Dessine des diagonales
	for (x = 0; x < MINIMAP_SIZE; x++)
	{
		minimap_set_pixel(img, x, x, 0xFFFFFFFF);                   // Diagonale
		minimap_set_pixel(img, x, MINIMAP_SIZE - 1 - x, 0x00FF00FF); // Diagonale /
	}

	// Dessiner un cadre intérieur bleu à 25% de la taille
	int margin = MINIMAP_SIZE / 4;
	for (x = margin; x < MINIMAP_SIZE - margin; x++)
	{
		minimap_set_pixel(img, x, margin, 0x0000FFFF);
		minimap_set_pixel(img, x, MINIMAP_SIZE - margin - 1, 0x0000FFFF);
	}

	for (y = margin; y < MINIMAP_SIZE - margin; y++)
	{
		minimap_set_pixel(img, margin, y, 0x0000FFFF);
		minimap_set_pixel(img, MINIMAP_SIZE - margin - 1, y, 0x0000FFFF);
	}
} */

static int	get_block_color(char block_type)
{
	if (block_type == '1')
		return (0x00EC1A1A);
	else if (block_type == '0')
		return (0x00837F7F);
	else if (block_type == 'D')
		return (0x006E2C00);
	else if (block_type == 'C')
		return (0x00F4D03F);
	else if (block_type == 'M')
		return (0x00800080);
	else if (block_type == 'N' || block_type == 'S' || \
			block_type == 'E' || block_type == 'W')
		return (0xFF2E86E1);
	return (0x002E4053);
}

static bool	is_valid_coord(t_main_struct *main_struct, int map_x, int map_y)
{
	int	i;

	if (map_x < 0 || map_y < 0)
		return (false);
	i = 0;
	while (main_struct->map[i])
		i++;
	if (map_y >= i)
		return (false);
	i = 0;
	while (main_struct->map[map_y] && main_struct->map[map_y][i])
		i++;
	if (map_x >= i)
		return (false);
	return (true);
}

bool	render_minimap(t_main_struct *main_struct, t_minimap *minimap)
{
	if (!main_struct->minimap)
		return (false);
	fill_minimap_background(main_struct->minimap);
	minimap->player_x = (int)floor(main_struct->player->x);
	minimap->player_y = (int)floor(main_struct->player->y);
	while (++minimap->y < MINIMAP_RADIUS * 2 + 1)
	{
		minimap->x = 0;
		while (minimap->x < MINIMAP_RADIUS * 2 + 1)
		{
			minimap->map_x = minimap->player_x + (minimap->x - MINIMAP_RADIUS);
			minimap->map_y = minimap->player_y + (minimap->y - MINIMAP_RADIUS);
			if (is_valid_coord(main_struct, minimap->map_x, minimap->map_y))
			{
				minimap->block_type = \
							main_struct->map[minimap->map_y][minimap->map_x];
				minimap->color = get_block_color(minimap->block_type);
				draw_square(main_struct->minimap,
					minimap->x, minimap->y, minimap->color);
			}
			minimap->x++;
		}
	}
	draw_player(main_struct->minimap);
	return (true);
}

bool	display_minimap(t_main_struct *main_struct)
{
	t_minimap	minimap;

	ft_memset(&minimap, 0, sizeof(t_minimap));
	minimap.y = -1;
	// test_fill_entire_image(main_struct->minimap);

	if (!render_minimap(main_struct, &minimap))
		return (false);
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr,
		main_struct->minimap->sprite, 20, 20);
	return (true);
}
