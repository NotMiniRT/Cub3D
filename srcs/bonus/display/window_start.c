#include "inputs_b.h"
#include "main_struct_b.h"
#include "mlx.h"
#include "common.h"
#include "image_b.h"
#include "display_b.h"
#include "player_b.h"
#include "parsing.h"
#include <stdio.h>
#include "fuel_bar.h"
#include "multithreading.h"
#include "torch.h"

#include "libft.h"

/**
 * @bug check les droits de fichiers avant de faire quoi que ce soit
 *
 */
static bool	init_all_sprites(t_main_struct *main_struct, t_infos *infos)
{
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_s), \
			infos->scene->so_texture)
		|| !get_image_cub_from_xpm(main_struct, &(main_struct->wall_o), \
			infos->scene->we_texture)
		|| !get_image_cub_from_xpm(main_struct, &(main_struct->wall_n), \
			infos->scene->no_texture)
		|| !get_image_cub_from_xpm(main_struct, &(main_struct->wall_e), \
			infos->scene->ea_texture)
		|| !create_img_cub(main_struct, &(main_struct->frame), \
			WINDOW_WIDTH, WINDOW_HEIGHT)
		|| !get_image_cub_from_xpm(main_struct, &(main_struct->fog), \
			"assets/textures/walls/fog.xpm")
		|| !get_image_cub_from_xpm(main_struct, &(main_struct->door), \
			"assets/textures/walls/door.xpm")
		|| !get_image_cub_from_xpm(main_struct, &(main_struct->potion), \
			"assets/textures/walls/potion.xpm")
		|| !create_img_cub(main_struct, &(main_struct->minimap), \
			WINDOW_HEIGHT / 3, WINDOW_HEIGHT / 3)
		|| !create_img_cub(main_struct, &(main_struct->fuel_bar), \
			HUD_WIDTH, HUD_HEIGHT))
		return (false);
	return (true);
}

static bool	init_display(t_main_struct *main_struct, t_infos *infos)
{
	main_struct->mlx_ptr = mlx_init();
	if (main_struct->mlx_ptr == NULL)
		return (false);
	main_struct->win_ptr = mlx_new_window(main_struct->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (main_struct->win_ptr == NULL)
		return (false);
	main_struct->player = malloc(sizeof(t_player));
	if (main_struct->player == NULL)
		return (false);
	if (!init_all_sprites(main_struct, infos))
		return (false);
	main_struct->ceil = *((int *)&(infos->scene->ceiling_color->b));
	main_struct->ground = *((int *)&(infos->scene->floor_color->b));
	main_struct->doors = &(infos->scene->door_positions);
	main_struct->items = &(infos->scene->collectible_positions);
	if (!init_r_h_tab(main_struct))
		return (false);
	init_player(main_struct->player, infos);
	main_struct->fuel = 15;
	if (!init_torch(main_struct))
		return (false);
	if (!init_threads(main_struct))
		return (false);
	if (!map_object_set(main_struct))
		return (false);
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
