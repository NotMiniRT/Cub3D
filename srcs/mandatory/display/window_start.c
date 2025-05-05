#include <stdlib.h>
#include "inputs.h"
#include "main_struct.h"
#include "mlx.h"
#include "common.h"
#include "image.h"
#include "display.h"
#include "player.h"

static int	init_display(t_main_struct *main_struct)
{
	main_struct->mlx_ptr = mlx_init();
	if (main_struct->mlx_ptr == NULL)
		return (1);
	main_struct->win_ptr = mlx_new_window(main_struct->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (main_struct->mlx_ptr == NULL)
		return (1);
	main_struct->player = malloc(sizeof(t_player));
	if (main_struct->player == NULL)
		return (1);
	if (create_img_cub(main_struct, &(main_struct->frame), WINDOW_WIDTH, WINDOW_HEIGHT))
		return (1);
	if (get_image_cub_from_xpm(main_struct, &(main_struct->wall), "./assets/textures/walls/wall_1.xpm"))
		return (1);
	init_player(main_struct->player);
	return (0);
}

static void	init_inputs(t_main_struct *main_struct)
{
	mlx_do_key_autorepeatoff(main_struct->mlx_ptr);
	mlx_loop_hook(main_struct->mlx_ptr, mlx_loop_action, main_struct);
	mlx_hook(main_struct->win_ptr, 2, 1L << 1, handle_input, main_struct);
	mlx_hook(main_struct->win_ptr, 3, 1L << 0, release_move, main_struct);
	mlx_hook(main_struct->win_ptr, 17, 1, on_destroy, main_struct);
}

int	start_display(t_main_struct *main_struct)
{
	if (init_display(main_struct))
		return (1);
	main_struct->map = malloc(sizeof(char *) * 11);
	main_struct->map[0]  = "111111111111111";
	main_struct->map[1]  = "110000000000011";
	main_struct->map[2]  = "110111111110011";
	main_struct->map[3]  = "110110000110011";
	main_struct->map[4]  = "110110000110011";
	main_struct->map[5]  = "110110000110011";
	main_struct->map[6]  = "110000000000011";
	main_struct->map[7]  = "110001001100011";
	main_struct->map[8]  = "110000110000011";
	main_struct->map[9]  = "001111111111111";
	main_struct->map[10] = NULL;
	
	main_struct->player->x = 4;
	main_struct->player->y = 8;
	init_inputs(main_struct);
	mlx_loop(main_struct->mlx_ptr);
	mlx_do_key_autorepeaton(main_struct->mlx_ptr);
	return (0);
}

