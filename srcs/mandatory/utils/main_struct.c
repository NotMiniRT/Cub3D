#include "main_struct.h"
#include <stdlib.h>
#include "mlx.h"

void	init_main_struct(t_main_struct *main_struct)
{
	main_struct->mlx_ptr = NULL;
	main_struct->win_ptr = NULL;
	main_struct->player = NULL;
	main_struct->map = NULL;
}
void	free_main_struct(t_main_struct *main_struct)
{
	// int	i;

	if (!main_struct)
		return ;
	if (main_struct->player != NULL)
		free(main_struct->player);
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