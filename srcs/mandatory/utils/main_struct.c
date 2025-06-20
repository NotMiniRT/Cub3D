/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:47:47 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:47:48 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "common.h"
#include "image.h"
#include "math.h"
#include "mlx.h"
#include "structs.h"

int	init_r_h_tab(t_main_struct *main_struct)
{
	int	i;

	main_struct->cos_r_h_tab = malloc(sizeof(double) * WINDOW_WIDTH);
	main_struct->r_h_tab = malloc(sizeof(double) * WINDOW_WIDTH);
	if (main_struct->cos_r_h_tab == NULL || main_struct->r_h_tab == NULL)
		return (false);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		main_struct->r_h_tab[i] = atan(2 * tan(FOVHALF)
				/ WINDOW_WIDTH * (i - WINDOW_WIDTH * 0.5));
		main_struct->cos_r_h_tab[i] = cos(main_struct->r_h_tab[i]);
		i++;
	}
	return (true);
}

void	free_main_struct_img(t_main_struct *main_struct)
{
	free_image_cub(main_struct, main_struct->frame);
	free_image_cub(main_struct, main_struct->wall_e);
	free_image_cub(main_struct, main_struct->wall_s);
	free_image_cub(main_struct, main_struct->wall_o);
	free_image_cub(main_struct, main_struct->wall_n);
	free_image_cub(main_struct, main_struct->fog);
}

void	free_main_struct(t_main_struct *main_struct)
{
	if (!main_struct)
		return ;
	if (main_struct->player != NULL)
		free(main_struct->player);
	free_main_struct_img(main_struct);
	if (main_struct->mlx_ptr != NULL && main_struct->win_ptr != NULL)
		mlx_destroy_window(main_struct->mlx_ptr, main_struct->win_ptr);
	if (main_struct->cos_r_h_tab != NULL)
		free(main_struct->cos_r_h_tab);
	if (main_struct->r_h_tab != NULL)
		free(main_struct->r_h_tab);
	if (main_struct->mlx_ptr != NULL)
	{
		mlx_destroy_display(main_struct->mlx_ptr);
		free(main_struct->mlx_ptr);
		main_struct->mlx_ptr = NULL;
	}
	main_struct->r_h_tab = NULL;
	main_struct->win_ptr = NULL;
	main_struct->cos_r_h_tab = NULL;
}

int	is_moving(t_main_struct *main_struct)
{
	if (main_struct->inputs[UP] + main_struct->inputs[DOWN] == 1
		|| main_struct->inputs[RIGHT] + main_struct->inputs[LEFT] == 1
		|| main_struct->inputs[TRIGHT] + main_struct->inputs[TLEFT] == 1)
		return (true);
	return (false);
}
