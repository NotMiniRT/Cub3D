#ifndef IMAGE_H
# define IMAGE_H

# include <stdbool.h>

# include "structs.h"

bool	create_img_cub(t_main_struct *main_struct, t_image_cub **img, int x, int y);
bool	get_image_cub_from_xpm(t_main_struct *main_struct, t_image_cub **img, char *path);
void	free_image_cub(t_main_struct *main_struct, t_image_cub *img);

#endif
