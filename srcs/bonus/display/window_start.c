#include "common.h"
#include "display_b.h"
#include "ft_dprintf.h"
#include "inputs_b.h"
#include "main_struct_b.h"
#include "mlx.h"
#include "monster.h"
#include "multithreading.h"
#include "parsing.h"
#include "player_b.h"
#include "sound.h"
#include "structs_b.h"
#include "torch.h"

#include <unistd.h>

static bool	init_display(t_main_struct *main_struct, t_infos *infos)
{
	main_struct->mlx_ptr = mlx_init();
	if (main_struct->mlx_ptr == NULL)
		return (false);
	main_struct->win_ptr = mlx_new_window(main_struct->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, CUB3D);
	if (main_struct->win_ptr == NULL)
		return (false);
	main_struct->player = malloc(sizeof(t_player));
	if (main_struct->player == NULL)
		return (false);
	main_struct->up_door = malloc(sizeof(t_lst_int *));
	if (main_struct->up_door == NULL)
		return (false);
	*(main_struct->up_door) = NULL;
	main_struct->down_door = malloc(sizeof(t_lst_int *));
	if (main_struct->down_door == NULL)
		return (false);
	*(main_struct->down_door) = NULL;
	if (!init_all_sprites(main_struct, infos))
		return (false);
	main_struct->ceil = *((int *)&(infos->scene->ceiling_color->b));
	main_struct->ground = *((int *)&(infos->scene->floor_color->b));
	main_struct->doors = &(infos->scene->door_positions);
	main_struct->items = &(infos->scene->collectible_positions);
	main_struct->collectible_count = infos->scene->collectible_count;
	if (infos->scene->monster_count == 0)
		main_struct->mj = NULL;
	else if (!set_mj(main_struct, infos))
		return (false);
	if (!init_r_h_tab(main_struct))
		return (false);
	init_player(main_struct->player, infos);
	main_struct->map[infos->scene->pos[1] - 1][infos->scene->pos[0] - 1] = '0';
	if (main_struct->mj != NULL)
		main_struct->map[infos->scene->monster_positions[1] - 1][infos->scene->monster_positions[0]- 1] = '0';
	main_struct->fuel = 1;
	if (!init_torch(main_struct))
		return (false);
	if (!init_threads(main_struct))
		return (false);
	if (!map_object_set(main_struct))
		return (false);
	if (!init_sound(main_struct))
		ft_dprintf(STDERR_FILENO, RED INIT_SOUND_FALSE RESET);
// 	if (!SOUND_ON)
// 		main_struct->sound = NULL;
// 	else if (!init_sound(main_struct))
// 		ft_dprintf(2, "Warning: Sound initialization failed\n");
	else
		ft_dprintf(2, GREEN INIT_SOUND_TRUE RESET);
	return (true);
}

static void	init_inputs(t_main_struct *main_struct)
{
	mlx_do_key_autorepeatoff(main_struct->mlx_ptr);
	mlx_loop_hook(main_struct->mlx_ptr, mlx_loop_action, main_struct);
	mlx_hook(main_struct->win_ptr, 2, 1L << 1, handle_input, main_struct);
	mlx_hook(main_struct->win_ptr, 3, 1L << 0, release_move, main_struct);
	mlx_hook(main_struct->win_ptr, 6, 1L << 6, handle_mouse_move, main_struct);
	mlx_hook(main_struct->win_ptr, 4, 1L << 2, handle_mouse_press, main_struct);
	mlx_hook(main_struct->win_ptr, 5, 1L << 3, handle_mouse_rl, main_struct);
	mlx_hook(main_struct->win_ptr, 17, 1, on_destroy, main_struct);
}

bool	start_display(t_main_struct *main_struct, t_infos *infos)
{
	main_struct->map = &(infos->data->lines[infos->map_start]);
	if (!init_display(main_struct, infos))
		return (false);
	init_inputs(main_struct);
	mlx_loop(main_struct->mlx_ptr);
	mlx_do_key_autorepeaton(main_struct->mlx_ptr);
	return (true);
}
