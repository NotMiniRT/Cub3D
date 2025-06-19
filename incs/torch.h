#ifndef TORCH_H
# define TORCH_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;

# define TORCH_WIDTH 64
# define TORCH_HEIGHT 64
# define TORCH_X 1300
# define TORCH_Y 800
# define FRAME_DURATION 150

# define T_ASSET_1 "assets/textures/fire/torch_1.xpm"
# define T_ASSET_2 "assets/textures/fire/torch_2.xpm"
# define T_ASSET_3 "assets/textures/fire/torch_3.xpm"
# define T_ASSET_4 "assets/textures/fire/torch_4.xpm"
# define T_ASSET_5 "assets/textures/fire/torch_5.xpm"

bool	display_torch(t_main_struct *main_struct);
bool	init_torch(t_main_struct *main_struct);

#endif
