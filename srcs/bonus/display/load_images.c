#include <unistd.h>

#include "common.h"
#include "ft_dprintf.h"
#include "fuel_bar.h"
#include "image_b.h"
#include "parsing.h"
#include "structs_b.h"

static bool	load_message(bool success, const char *item_name)
{
	if (success)
		ft_dprintf(STDOUT_FILENO, CYAN SUCCESS_LOAD, item_name, RESET);
	else
		ft_dprintf(STDERR_FILENO, RED ERROR_LOAD, item_name, RESET);
	return (success);
}

static bool	load_walls(t_main_struct *main_struct, t_infos *infos)
{
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_s),
			infos->scene->so_texture, 2048))
		return (load_message(false, S_WALL_TEXTURE));
	load_message(true, S_WALL_TEXTURE);
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_o),
			infos->scene->we_texture, 2048))
		return (load_message(false, W_WALL_TEXTURE));
	load_message(true, W_WALL_TEXTURE);
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_n),
			infos->scene->no_texture, 2048))
		return (load_message(false, N_WALL_TEXTURE));
	load_message(true, N_WALL_TEXTURE);
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_e),
			infos->scene->ea_texture, 2048))
		return (load_message(false, E_WALL_TEXTURE));
	load_message(true, E_WALL_TEXTURE);
	return (true);
}

static bool	load_frame_buffer(t_main_struct *main_struct)
{
	if (!create_img_cub(main_struct, &(main_struct->frame),
			WINDOW_WIDTH, WINDOW_HEIGHT))
		return (load_message(false, FRAME_BUFFER));
	load_message(true, FRAME_BUFFER);
	return (true);
}

static bool	load_environment_textures(t_main_struct *main_struct)
{
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->fog),
			FOG_ASSET, 64))
		return (load_message(false, FOG_TEXTURE));
	load_message(true, FOG_TEXTURE);
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->door),
			DOOR_TEXTURE, 2048))
		return (load_message(false, DOOR_ASSET));
	load_message(true, DOOR_ASSET);
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->potion),
			POTION_ASSET, 64))
		return (load_message(false, POTION_TEXTURE));
	load_message(true, POTION_TEXTURE);
	if (!create_img_cub(main_struct, &(main_struct->minimap),
			WINDOW_HEIGHT / 3, WINDOW_HEIGHT / 3))
		return (load_message(false, MINIMAP_MESSAGE));
	load_message(true, MINIMAP_MESSAGE);
	if (!create_img_cub(main_struct, &(main_struct->fuel_bar),
			HUD_WIDTH, HUD_HEIGHT))
		return (load_message(false, FUEL_BAR_MESSAGE));
	load_message(true, FUEL_BAR_MESSAGE);
	return (true);
}

bool	init_all_sprites(t_main_struct *main_struct, t_infos *infos)
{
	if (!load_walls(main_struct, infos))
		return (false);
	if (!load_frame_buffer(main_struct))
		return (false);
	if (!load_environment_textures(main_struct))
		return (false);
	return (true);
}
