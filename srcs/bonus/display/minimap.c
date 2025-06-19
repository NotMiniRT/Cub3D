#include <math.h>

#include "common.h"
#include "image_b.h"
#include "libft.h"
#include "minimap.h"
#include "structs_b.h"

static int	get_block_color(char block_type)
{
	if (block_type == '1')
		return (0x00203050);
	else if (block_type == '0')
		return (0x00152035);
	else if (block_type == 'D')
		return (0x00303050 + 100);
	else if (block_type == 'C')
		return (0x00304060 + 50);
	else if (block_type == 'M')
		return (0x00404870);
	else if (block_type == 'N' || block_type == 'S' || \
			block_type == 'E' || block_type == 'W')
		return (0x00305070);
	return (0x00101825);
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

static void	init_offset_fractional(t_main_struct *main_struct, \
															t_minimap *minimap)
{
	minimap->y = -1;
	minimap->player_x = (int)floor(main_struct->player->x);
	minimap->player_y = (int)floor(main_struct->player->y);
	minimap->fractional_x = main_struct->player->x - 0.25 - minimap->player_x;
	minimap->fractional_y = main_struct->player->y - 0.25 - minimap->player_y;
	minimap->block_size = (WINDOW_HEIGHT / 3) / (MINIMAP_RADIUS * 2);
	minimap->offset_x = minimap->fractional_x * minimap->block_size;
	minimap->offset_y = minimap->fractional_y * minimap->block_size;
}

static bool	render_minimap(t_main_struct *main_struct, t_minimap *minimap)
{
	if (!main_struct->minimap)
		return (false);
	fill_minimap_background(main_struct->minimap);
	init_offset_fractional(main_struct, minimap);
	while (++minimap->y < MINIMAP_RADIUS * 2 + 2)
	{
		minimap->x = 0;
		minimap->map_y = minimap->player_y + (minimap->y - MINIMAP_RADIUS);
		while (minimap->x < MINIMAP_RADIUS * 2 + 2)
		{
			minimap->map_x = minimap->player_x + (minimap->x - MINIMAP_RADIUS);
			if (is_valid_coord(main_struct, minimap->map_x, minimap->map_y))
			{
				minimap->block_type = \
							main_struct->map[minimap->map_y][minimap->map_x];
				minimap->color = get_block_color(minimap->block_type);
				draw_square_with_offset(main_struct->minimap, minimap);
			}
			minimap->x++;
		}
	}
	draw_player(main_struct->minimap, main_struct->player->fov_angle);
	return (true);
}

bool	display_minimap(t_main_struct *main_struct)
{
	t_minimap	minimap;
	int			i;
	int			j;

	ft_memset(&minimap, 0, sizeof(t_minimap));
	if (!render_minimap(main_struct, &minimap))
		return (false);
	i = 0;
	while (i < WINDOW_HEIGHT * 0.3333)
	{
		j = 0;
		while (j < WINDOW_HEIGHT * 1.3333)
		{
			change_pixel_color(main_struct->frame, \
					get_color(main_struct->minimap, j, i), 80 + j, 20 + i);
			j = j + 4;
		}
		i++;
	}
	return (true);
}
