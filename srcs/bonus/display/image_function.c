#include "common.h"
#include "structs_b.h"
#include "mlx.h"
#include <stdbool.h>
#include "image_b.h"

int	create_img_cub(t_main_struct *main_struct, t_image_cub **img, int x, int y)
{
	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)
		return (false);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->size = x;
	(*img)->sprite = mlx_new_image(main_struct->mlx_ptr, x, y);
	if ((*img)->sprite == NULL)
		return (false);
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits),
			&((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
		return (false);
	return (true);
}

static int	rotate_img(t_main_struct *main_struct, t_image_cub **img, int size)
{
	int			x;
	int			y;
	t_image_cub	*new_img;

	y = 0;
	if (!create_img_cub(main_struct, &new_img, size, size))
		return (false);
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			change_pixel_color(new_img, get_color(*img, x * 4, y), y * 4, x);
			x++;
		}
		y++;
	}
	free_image_cub(main_struct, *img);
	*img = new_img;
	return (true);
}

int	get_image_cub_from_xpm_no_rot(t_main_struct *main_struct,
	t_image_cub **img, char *path, int size)
{
	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)
		return (false);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->size = size;
	(*img)->sprite = mlx_xpm_file_to_image(main_struct->mlx_ptr, path, &size, &size);
	if ((*img)->sprite == NULL)
		return (false);
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits),
			&((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
		return (false);
	return (true);
}

int	get_image_cub_from_xpm(t_main_struct *main_struct,
		t_image_cub **img, char *path, int size)
{
	(*img) = NULL;
	(*img) = malloc(sizeof(t_image_cub));
	if ((*img) == NULL)
		return (false);
	(*img)->buffer = NULL;
	(*img)->sprite = NULL;
	(*img)->size = size;
	(*img)->sprite = mlx_xpm_file_to_image(main_struct->mlx_ptr, path, &size, &size);
	if ((*img)->sprite == NULL)
		return (false);
	(*img)->buffer = mlx_get_data_addr((*img)->sprite, &((*img)->pixel_bits),
			&((*img)->line_bytes), &((*img)->endian));
	if ((*img)->buffer == NULL)
		return (false);
	if (!rotate_img(main_struct, img, size))
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
