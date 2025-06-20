/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:43:05 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:43:05 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_b.h"

int	get_color(t_image_cub *img, int texture_x, int texture_y)
{
	return (((int *)(img->buffer + (texture_y * img->line_bytes)
			+ (texture_x)))[0]);
}

void	change_pixel_color(t_image_cub *img, int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}
