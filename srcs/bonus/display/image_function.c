#include "structs_b.h" // a enlever de image_b.h
#include "mlx.h"
#include "image_b.h"

int	create_img_cub(t_main_struct *main_struct, t_image_cub **img, int x, int y)
{
	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)
		return (false);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->sprite = mlx_new_image(main_struct->mlx_ptr, x, y);
	if ((*img)->sprite == NULL)
	{
		free(*img);
		*img = NULL;
		return (false);
	}
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits),
			&((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
	{
		mlx_destroy_image(main_struct->mlx_ptr, (*img)->sprite);
		free(*img);
		*img = NULL;
		return (false);
	}
	(*img)->width = x;
	(*img)->height = y;
	return (true);
}

static int	get_rotated_pixel(t_image_cub *src, int x, int y)
{
	int	offset;
	int	color;

	if (x < 0 || x >= src->width || y < 0 || y >= src->height)
		return (0);
	offset = (y * src->line_bytes) + (x * (src->pixel_bits / 8));
	color = *(int *)(src->buffer + offset);
	return (color);
}

static void	set_rotated_pixel(t_image_cub *dst, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= dst->width || y < 0 || y >= dst->height)
		return ;
	offset = (y * dst->line_bytes) + (x * (dst->pixel_bits / 8));
	*(int *)(dst->buffer + offset) = color;
}

static int	rotate_img(t_main_struct *main_struct, t_image_cub **img)
{
	int			x;
	int			y;
	t_image_cub	*new_img;
	t_image_cub	*src_img;
	int			color;

	src_img = *img;
	if (!create_img_cub(main_struct, &new_img,
			src_img->height, src_img->width))
		return (false);
	y = 0;
	while (y < src_img->height)
	{
		x = 0;
		while (x < src_img->width)
		{
			color = get_rotated_pixel(src_img, x, y);
			set_rotated_pixel(new_img, y, x, color);
			x++;
		}
		y++;
	}
	free_image_cub(main_struct, *img);
	*img = new_img;
	return (true);
}

int	get_image_cub_from_xpm_no_rot(t_main_struct *main_struct,
	t_image_cub **img, char *path)
{
	int	width;
	int	height;

	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)
		return (false);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->sprite = mlx_xpm_file_to_image(main_struct->mlx_ptr,
		path, &width, &height);
	if ((*img)->sprite == NULL)
	{
		free(*img);
		*img = NULL;
		return (false);
	}
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits),
			&((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
	{
		mlx_destroy_image(main_struct->mlx_ptr, (*img)->sprite);
		free(*img);
		*img = NULL;
		return (false);
	}
	(*img)->width = width;
	(*img)->height = height;
	return (true);
}

int	get_image_cub_from_xpm(t_main_struct *main_struct,
		t_image_cub **img, char *path)
{
	int	width;
	int	height;

	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)
		return (false);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->sprite = mlx_xpm_file_to_image(main_struct->mlx_ptr,
		path, &width, &height);
	if ((*img)->sprite == NULL)
	{
		free(*img);
		*img = NULL;
		return (false);
	}
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits),
			&((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
	{
		mlx_destroy_image(main_struct->mlx_ptr, (*img)->sprite);
		free(*img);
		*img = NULL;
		return (false);
	}
	(*img)->width = width;
	(*img)->height = height;
	if (!rotate_img(main_struct, img))
		return (false);
	return (true);
}

void	free_image_cub(t_main_struct *main_struct, t_image_cub *img)
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
