#include "main_struct.h"
#include <stdlib.h>
#include "mlx.h"
#include "image.h"
#include "math.h"

int init_R_H_tab(t_main_struct *main_struct)
{
	int i;

	main_struct->cos_R_H_tab = malloc(sizeof(double) * WINDOW_WIDTH);
	main_struct->R_H_tab = malloc(sizeof(double) * WINDOW_WIDTH);
	if (main_struct->cos_R_H_tab == NULL || main_struct->R_H_tab == NULL)
		return (1);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		main_struct->R_H_tab[i] = atan(2 * tan(FOV / 2) / WINDOW_WIDTH * (i - WINDOW_WIDTH * 0.5));
		main_struct->cos_R_H_tab[i] = cos(main_struct->R_H_tab[i]);
		i++;
	}
	return (0);
}

void	init_main_struct(t_main_struct *main_struct)
{
	main_struct->mlx_ptr = NULL;
	main_struct->win_ptr = NULL;
	main_struct->player = NULL;
	main_struct->map = NULL;
	main_struct->cos_R_H_tab = NULL;
	main_struct->R_H_tab = NULL;
	main_struct->created_at = 0;
	main_struct->last_move = 0;
	main_struct->inputs[UP] = 0;
	main_struct->inputs[DOWN] = 0;
	main_struct->inputs[RIGHT] = 0;
	main_struct->inputs[LEFT] = 0;
	main_struct->inputs[TRIGHT] = 0;
	main_struct->inputs[TLEFT] = 0;
	main_struct->inputs[SHIFT] = 0;
}
void	free_main_struct(t_main_struct *main_struct)
{
	// int	i;

	if (!main_struct)
		return ;
	if (main_struct->player != NULL)
		free(main_struct->player);
	free_image_cub(main_struct, main_struct->frame);
	if (main_struct->mlx_ptr != NULL && main_struct->win_ptr != NULL)
	{
		mlx_destroy_window(main_struct->mlx_ptr, main_struct->win_ptr);
		main_struct->win_ptr = NULL;
	}
	if (main_struct->mlx_ptr != NULL)
	{
		mlx_destroy_display(main_struct->mlx_ptr);
		free(main_struct->mlx_ptr);
		main_struct->mlx_ptr = NULL;
	}
	if (main_struct->cos_R_H_tab != NULL)
	{
		free(main_struct->cos_R_H_tab);
		main_struct->cos_R_H_tab = NULL;
	}
	if (main_struct->R_H_tab != NULL)
	{
		free(main_struct->R_H_tab);
		main_struct->R_H_tab = NULL;
	}
	free(main_struct->map);
	// if (main_struct->map != NULL)
	// {
	// 	i = 0;
	// 	while(main_struct->map[i])
	// 	{
	// 		free(main_struct->map[i]);
	// 		i++;
	// 	}
	// 	free(main_struct->map);
	// 	main_struct->map = NULL;
	// }
}

int is_moving(t_main_struct *main_struct)
{
	if (main_struct->inputs[UP] + main_struct->inputs[DOWN] == 1
		|| main_struct->inputs[RIGHT] + main_struct->inputs[LEFT] == 1
		|| main_struct->inputs[TRIGHT] + main_struct->inputs[TLEFT] == 1)
		return (1);
	return (0);
}