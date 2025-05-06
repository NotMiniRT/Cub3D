#ifndef COMMON_H
# define COMMON_H

#include "main_struct.h"

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920
# define DRUG_FOV 1.5471975512
# define FOV 1.0471975512
# define ROT_SPEED 0.12
# define PLAYER_SPEED 0.06
# define PI 3.14159265359f
# define FOVHALF FOV * 0.5
# define FOVSWINDOW_WIDTH FOV / WINDOW_WIDTH
# define DISTANCE_SCALE_FACTOR 1.5
int	start_display(t_main_struct *main_struct);

#endif
