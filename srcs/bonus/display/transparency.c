/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:12 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:44:13 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_b.h"

static inline int	darken_color(int color, float factor)
{
	return (((int)(((color >> 16) & 0xFF) * factor) << 16) |
		((int)(((color >> 8) & 0xFF) * factor) << 8)
		| (int)(((color) & 0xFF) * factor));
}

static inline void	change_pixel_color_opt(t_image_cub *img,
		int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}

static int	one_item_transparency(t_object_hit object_hit,
	t_main_struct *main_struct, int row, int j)
{
	int	text_y;
	int	color;

	text_y = (int)object_hit.text_y_index;
	if (object_hit.type == DOOR && object_hit.status != 100)
		text_y = text_y - (int)(main_struct->door->size
				* (0.8 - object_hit.status * 0.008));
	if (text_y < 0)
		text_y = 0;
	if (text_y >= main_struct->door->size)
		text_y = main_struct->door->size - 1;
	color = (object_hit.line_add + text_y)[0];
	if (color != 0)
	{
		change_pixel_color_opt(main_struct->frame,
			darken_color(color,
				object_hit.dark_factor), row, j);
		return (1);
	}
	return (0);
}

int	put_transparency(t_render_calculus *render_calc,
	t_main_struct *main_struct, int row, int j)
{
	int	i;

	i = 0;
	while (i < render_calc->res[4])
	{
		if (((render_calc->hit_tab[i].type == ITEM
					&& render_calc->hit_tab[i].status != 0)
				|| render_calc->hit_tab[i].type == DOOR
				|| render_calc->hit_tab[i].type == MONSTER)
			&& j < render_calc->hit_tab[i].height_check_plus
			&& j > render_calc->hit_tab[i].height_check_minus
			&& one_item_transparency(render_calc->hit_tab[i],
				main_struct, row, j))
			return (1);
		i++;
	}
	return (0);
}
