#ifndef IMAGE_H
# define IMAGE_H

#include "main_struct.h"

typedef struct s_image_cub
{
	void *sprite;
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer;
} t_image_cub;

void	change_pixel_color(t_image_cub *img, int color, int x, int y);
int create_img(t_main_struct *main_struct, t_image_cub *img);

#endif