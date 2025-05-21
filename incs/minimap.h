#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdbool.h>

# include "structs_b.h"

# define MINIMAP_RADIUS 9
# define PLAYER_DOT_SIZE 6

bool	display_minimap(t_main_struct *main_struct);
bool	overlay(t_main_struct *main_struct);

void	draw_square_with_offset(t_image_cub *img, t_minimap *minimap);
void	draw_player(t_image_cub *img, double angle);
void	fill_minimap_background(t_image_cub *img);

#endif
