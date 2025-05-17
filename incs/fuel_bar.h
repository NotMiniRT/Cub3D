#ifndef HUD_H
# define HUD_H

# include <stdbool.h>
# include "structs.h"

# define HUD_WIDTH 60           // Réduit la largeur (était 150)
# define HUD_HEIGHT 450         // Ajusté également
# define HUD_X 20               // Position X ajustée
# define HUD_Y 420              // Position plus basse (était 120)
# define GAUGE_WIDTH 30         // Jauge plus fine (était 40)
# define GAUGE_HEIGHT 370       // Hauteur ajustée
# define GAUGE_X 15             // Position X de la jauge centrée
# define GAUGE_Y 65             // Position Y de la jauge dans le HUD
# define GAUGE_BORDER 2			

bool	display_hud(t_main_struct *main_struct);
void	draw_fuel_gauge(t_image_cub *img, int fuel_level);
void	hud_set_pixel(t_image_cub *img, int x, int y, int color);

#endif
