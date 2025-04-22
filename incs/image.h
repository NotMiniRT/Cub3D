#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_image_cub
{
	void *sprite;
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer;
} t_image_cub;

#endif