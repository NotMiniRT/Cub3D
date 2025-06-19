#ifndef TORCH_H
# define TORCH_H

# include <stdbool.h>

# include "structs_b.h"

# define TORCH_WIDTH 64    // Width of the torch image
# define TORCH_HEIGHT 64   // Height of the torch image
# define TORCH_X 1300       // Position X of the torch on screen
# define TORCH_Y 800        // Position Y of the torch on screen
# define FRAME_DURATION 150 // Milliseconds between animation frames

bool	display_torch(t_main_struct *main_struct);
bool	init_torch(t_main_struct *main_struct);

#endif
