#include "image.h"
#include "common.h"
#include "main_struct.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int	get_color(t_image_cub *img, int texture_x, int texture_y)
{
	return (((int *)(img->buffer + (texture_y * img->line_bytes) + (texture_x)))[0]);
}

void	change_pixel_color(t_image_cub *img, int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}

static int rotate_img(t_main_struct *main_struct, t_image_cub **img)
{
	int x;
	int y;

	t_image_cub *new_img;

	y = 0;
	if (create_img_cub(main_struct, &new_img, 64, 64))
		return (1);
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			change_pixel_color(new_img, get_color(*img, x * 4, y), y * 4, x);
			x++;
		}
		y++;
	}
	free_image_cub(main_struct, *img);
	*img = new_img;
	return (0);
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
	if (rotate_img(main_struct, img))
		return (1);
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