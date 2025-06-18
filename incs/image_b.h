#ifndef IMAGE_B_H
# define IMAGE_B_H

# include "structs_b.h"
# include <stdbool.h>

int		create_img_cub(t_main_struct *main_struct,
			t_image_cub **img, int x, int y);
int		get_image_cub_from_xpm(t_main_struct *main_struct,
			t_image_cub **img, char *path, int size);
int		get_color(t_image_cub *img, int texture_x, int texture_y);
void	free_image_cub(t_main_struct *main_struct, t_image_cub *img);
void	change_pixel_color(t_image_cub *img, int color, int x, int y);
int		get_image_cub_from_xpm_no_rot(t_main_struct *main_struct, \
									t_image_cub **img, char *path, int size);

#endif
