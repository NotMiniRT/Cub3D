#include "main_struct.h"
#include <stdlib.h>
#include "mlx.h"

void	init_main_struct(t_main_struct *main_struct)
{
	main_struct->mlx_ptr = NULL;
	main_struct->win_ptr = NULL;
	main_struct->player = NULL;
}
void	free_main_struct(t_main_struct *main_struct)
{
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
}