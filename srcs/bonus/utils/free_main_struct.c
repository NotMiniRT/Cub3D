#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"
#include "image_b.h"
#include "lst_int.h"
#include "main_struct_b.h"
#include "mlx.h"
#include "multithreading.h"
#include "structs_b.h"

static void	free_michael_jackson(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	if (main_struct->mj->sprite != NULL)
	{
		while (i < MJ_SPRITES)
		{
			if ((main_struct->mj->sprite)[i] != NULL)
				free_image_cub(main_struct, (main_struct->mj->sprite)[i]);
			else
				break ;
			i++;
		}
		free(main_struct->mj->sprite);
	}
	free(main_struct->mj);
}

void	free_main_struct_img(t_main_struct *main_struct)
{
	int	i;

	free_image_cub(main_struct, main_struct->frame);
	free_image_cub(main_struct, main_struct->wall_e);
	free_image_cub(main_struct, main_struct->wall_s);
	free_image_cub(main_struct, main_struct->wall_o);
	free_image_cub(main_struct, main_struct->wall_n);
	free_image_cub(main_struct, main_struct->potion);
	free_image_cub(main_struct, main_struct->door);
	free_image_cub(main_struct, main_struct->minimap);
	free_image_cub(main_struct, main_struct->fuel_bar);
	free_image_cub(main_struct, main_struct->fog);
	if (main_struct->torch)
	{
		i = 0;
		while (i < 5)
		{
			if (main_struct->torch->frames[i])
				free_image_cub(main_struct, main_struct->torch->frames[i]);
			i++;
		}
		free(main_struct->torch);
		main_struct->torch = NULL;
	}
}

void	free_main_struct_second_part(t_main_struct *main_struct)
{
	if (main_struct->mj != NULL)
		free_michael_jackson(main_struct);
	if (main_struct->up_door != NULL)
	{
		free_lst_int(*(main_struct->up_door));
		free(main_struct->up_door);
	}
	if (main_struct->mlx_ptr != NULL)
	{
		mlx_destroy_display(main_struct->mlx_ptr);
		free(main_struct->mlx_ptr);
		main_struct->mlx_ptr = NULL;
	}
	main_struct->r_h_tab = NULL;
	main_struct->win_ptr = NULL;
	main_struct->cos_r_h_tab = NULL;
	cleanup_threads(main_struct->thread_manager);
}

void	free_main_struct_first_part(t_main_struct *main_struct)
{
	if (!main_struct)
		return ;
	free_main_struct_img(main_struct);
	if (main_struct->map_items != NULL)
		free_map_item_ij(main_struct);
	if (main_struct->player != NULL)
		free(main_struct->player);
	if (main_struct->mlx_ptr != NULL && main_struct->win_ptr != NULL)
		mlx_destroy_window(main_struct->mlx_ptr, main_struct->win_ptr);
	if (main_struct->cos_r_h_tab != NULL)
		free(main_struct->cos_r_h_tab);
	if (main_struct->r_h_tab != NULL)
		free(main_struct->r_h_tab);
	if (main_struct->down_door != NULL)
	{
		free_lst_int(*(main_struct->down_door));
		free(main_struct->down_door);
	}
	free_main_struct_second_part(main_struct);
}
