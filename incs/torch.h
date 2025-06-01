#ifndef TORCH_H
# define TORCH_H

# include <stdbool.h>
# include "structs_b.h"

# define TORCH_WIDTH 64    // Width of the torch image
# define TORCH_HEIGHT 64   // Height of the torch image
# define TORCH_X 1300       // Position X of the torch on screen
# define TORCH_Y 600        // Position Y of the torch on screen
# define FRAME_DURATION 150 // Milliseconds between animation frames

# define TORCH_DISPLAY_X 1250       // Position X de la torche sur l'écran
# define TORCH_DISPLAY_Y 550        // Position Y de la torche sur l'écran
# define TORCH_DISPLAY_SCALE 8      // Facteur de mise à l'échelle (8 pour 64x64 = 512x512)
# define TORCH_FRAME_COUNT 4        // Nombre de frames d'animation
# define TORCH_FRAME_DURATION 150   // Millisecondes entre les frames


# define TORCH_FRAME_1 "assets/textures/torch/torch_1.xpm"
# define TORCH_FRAME_2 "assets/textures/torch/torch_2.xpm"
# define TORCH_FRAME_3 "assets/textures/torch/torch_3.xpm"
# define TORCH_FRAME_4 "assets/textures/torch/torch_4.xpm"

bool    display_torch(t_main_struct *main_struct);
bool    init_torch(t_main_struct *main_struct);

#endif
