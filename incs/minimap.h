#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdbool.h>

# include "minimap.h"
# include "structs.h"

# define MINIMAP_RADIUS 12
# define PLAYER_DOT_SIZE 6

bool	display_minimap(t_main_struct *main_struct);
bool	overlay(t_main_struct *main_struct);

void	draw_square(t_image_cub *img, int x, int y, int color);
void	draw_player(t_image_cub *img);
void	fill_minimap_background(t_image_cub *img);

#endif
