#include "image.h"
#include "common.h"
#include "main_struct.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int	get_color(t_image_cub *img, int texture_x, int texture_y)
{
	double pixel;

	pixel = (texture_y * img->line_bytes) + (texture_x * 4);

	unsigned char b = img->buffer[(int)pixel + 0];
	unsigned char g = img->buffer[(int)pixel + 1];
	unsigned char r = img->buffer[(int)pixel + 2];
	unsigned char a = img->buffer[(int)pixel + 3];
	
	return ((int)((a << 24) | (r << 16) | (g << 8) | b));
}

void	change_pixel_color(t_image_cub *img, int color, int x, int y)
{
	int pixel;
	
	pixel = (y * img->line_bytes) + (x * 4);

	img->buffer[pixel + 0] = (color) & 0xFF;
	img->buffer[pixel + 1] = (color >> 8) & 0xFF;
	img->buffer[pixel + 2] = (color >> 16) & 0xFF;
	img->buffer[pixel + 3] = (color >> 24);
}

int get_image_cub_from_xpm(t_main_struct *main_struct, t_image_cub **img, char *path)
{
	int s;

	s = 64;
	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)	
		return (1);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->sprite = mlx_xpm_file_to_image(main_struct->mlx_ptr, path, &s, &s);
	if ((*img)->sprite == NULL)
		return (1);
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits), &((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
		return(1);
	return (0);
}

int create_img_cub(t_main_struct *main_struct, t_image_cub **img, int x, int y)
{
	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)	
		return (1);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->sprite = mlx_new_image(main_struct->mlx_ptr, x, y);
	if ((*img)->sprite == NULL)
		return (1);
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits), &((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
		return(1);
	return (0);
}

void free_image_cub(t_main_struct *main_struct, t_image_cub *img)
{
	if (img && img->sprite && main_struct->mlx_ptr)
	{
		mlx_destroy_image(main_struct->mlx_ptr, img->sprite);
		img->sprite = NULL;
	}
	if (img)
	{
		free(img);
		img = NULL;
	}
}