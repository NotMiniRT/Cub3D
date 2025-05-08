#ifndef IMAGE_H
# define IMAGE_H

#include "structs.h"

int 	create_img_cub(t_main_struct *main_struct, t_image_cub **img, int x, int y);
void	free_image_cub(t_main_struct *main_struct, t_image_cub *img);
int get_image_cub_from_xpm(t_main_struct *main_struct, t_image_cub **img, char *path);
int	get_color(t_image_cub *img, int texture_x, int texture_y);
void	change_pixel_color(t_image_cub *img, int color, int x, int y);

#endif