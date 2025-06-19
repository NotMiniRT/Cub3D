#ifndef TORCH_H
# define TORCH_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;

# define TORCH_WIDTH 64    
# define TORCH_HEIGHT 64
# define TORCH_X 1300
# define TORCH_Y 800
# define FRAME_DURATION 150

bool	display_torch(t_main_struct *main_struct);
bool	init_torch(t_main_struct *main_struct);

#endif
