#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdbool.h>

# include "structs_b.h"

# define MINIMAP_RADIUS 9
# define PLAYER_DOT_SIZE 6

# define MINIMAP_WALL_COLOR 0x00203050
# define MINIMAP_FLOOR_COLOR 0x00152035
# define MINIMAP_DOOR_COLOR 0x005050B4
# define MINIMAP_ITEM_COLOR 0x00304092
# define MINIMAP_MONSTER_COLOR 0x00404870
# define MINIMAP_DIRECTION_COLOR 0x00305070
# define MINIMAP_DEFAULT_COLOR 0x00101825

bool	display_minimap(t_main_struct *main_struct);
bool	overlay(t_main_struct *main_struct);

void	draw_square_with_offset(t_image_cub *img, t_minimap *minimap);
void	draw_player(t_image_cub *img, double angle);
void	fill_minimap_background(t_image_cub *img);

#endif



