#ifndef HUD_H
# define HUD_H

# include <stdbool.h>
# include "structs.h"

# define HUD_WIDTH 240           // Largeur de la fenetre
# define HUD_HEIGHT 450         // Longueur de la fenetre
# define HUD_X 80               // Position X de l'HUD
# define HUD_Y 420              // Position Y de l'HUD
# define GAUGE_WIDTH 30         // Largeur de la jauge
# define GAUGE_HEIGHT 370       // Longueur de la jauge
# define GAUGE_X 15             // Position X de la jauge centrée
# define GAUGE_Y 65             // Position Y de la jauge dans le HUD
# define GAUGE_BORDER 2

bool	display_hud(t_main_struct *main_struct);
void	draw_fuel_gauge(t_image_cub *img, int fuel_level);
void	hud_set_pixel(t_image_cub *img, int x, int y, int color);

#endif
