#include <stdlib.h>
#include "inputs.h"
#include "main_struct.h"
#include "mlx.h"

static int	init_display(t_main_struct *main_struct)
{
	main_struct->mlx_ptr = mlx_init();
	if (main_struct->mlx_ptr == NULL)
		return (1);
	main_struct->win_ptr = mlx_new_window(main_struct->mlx_ptr, 1920, 1080, "cub3D");
	if (main_struct->mlx_ptr == NULL)
		return (1);
	return (0);
}

static void	init_inputs(t_main_struct *main_struct)
{
	mlx_do_key_autorepeatoff(main_struct->mlx_ptr);
	mlx_hook(main_struct->win_ptr, 3, 1L << 1, handle_input, main_struct);
	mlx_hook(main_struct->win_ptr, 17, 1, on_destroy, main_struct);
}

int	start_display(t_main_struct *main_struct)
{
	if (init_display(main_struct))
		return (1);
	init_inputs(main_struct);
	mlx_loop(main_struct->mlx_ptr);
	mlx_do_key_autorepeaton(main_struct->mlx_ptr);
	return (0);
}

