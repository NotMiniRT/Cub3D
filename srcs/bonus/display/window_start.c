#include "inputs.h"
#include "main_struct.h"
#include "mlx.h"
#include "common.h"
#include "image.h"
#include "display.h"
#include "player.h"
#include "parsing.h"
#include <stdio.h>

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
			"assets/textures/walls/fog.xpm"))
		// || !create_img_cub(main_struct, &(main_struct->minimap), \
			// WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.17)) // define plus tard
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
	if (!init_r_h_tab(main_struct))
		return (false);
	init_player(main_struct->player, infos);
	return (true);
}

static void	init_inputs(t_main_struct *main_struct)
{
	mlx_do_key_autorepeatoff(main_struct->mlx_ptr);
	mlx_loop_hook(main_struct->mlx_ptr, mlx_loop_action, main_struct);
	mlx_hook(main_struct->win_ptr, 2, 1L << 1, handle_input, main_struct);
	mlx_hook(main_struct->win_ptr, 3, 1L << 0, release_move, main_struct);
	mlx_hook(main_struct->win_ptr, 17, 1, on_destroy, main_struct);
}

bool	start_display(t_main_struct *main_struct, t_infos *infos)
{
	if (!init_display(main_struct, infos))
		return (false);
	main_struct->map = &(infos->data->lines[infos->map_start]);
	init_inputs(main_struct);
	mlx_loop(main_struct->mlx_ptr);
	mlx_do_key_autorepeaton(main_struct->mlx_ptr);
	return (true);
}
