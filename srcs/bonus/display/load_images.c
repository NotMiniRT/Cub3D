#include "common.h"
#include "display_b.h"
#include "fuel_bar.h"
#include "image_b.h"
#include "inputs_b.h"
#include "libft.h"
#include "main_struct_b.h"
#include "mlx.h"
#include "monster.h"
#include "multithreading.h"
#include "parsing.h"
#include "player_b.h"
#include "timer_b.h"
#include "torch.h"

#include <stdio.h>
#include <unistd.h>

#include "sound.h"
#include "ft_dprintf.h"

static bool	load_message(bool success, const char *item_name)
{
	if (success)
		ft_dprintf(STDOUT_FILENO, CYAN "✓ Successfully loaded %s%s\n", item_name, RESET);
	else
		ft_dprintf(STDERR_FILENO, RED "✗ Error loading %s%s\n", item_name, RESET);
	return (success);
}

static bool	load_walls(t_main_struct *main_struct, t_infos *infos)
{
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_s),
			infos->scene->so_texture, 2048))
		return (load_message(false, "south wall texture"));
	load_message(true, "south wall texture");
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_o),
			infos->scene->we_texture, 2048))
		return (load_message(false, "west wall texture"));
	load_message(true, "west wall texture");
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_n),
			infos->scene->no_texture, 2048))
		return (load_message(false, "north wall texture"));
	load_message(true, "north wall texture");
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->wall_e),
			infos->scene->ea_texture, 2048))
		return (load_message(false, "east wall texture"));
	load_message(true, "east wall texture");
	return (true);
}

static bool	load_frame_buffer(t_main_struct *main_struct)
{
	if (!create_img_cub(main_struct, &(main_struct->frame),
			WINDOW_WIDTH, WINDOW_HEIGHT))
		return (load_message(false, "frame buffer"));
	load_message(true, "frame buffer");
	return (true);
}

static bool	load_environment_textures(t_main_struct *main_struct)
{
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->fog),
			"assets/textures/walls/fog.xpm", 64))
		return (load_message(false, "fog texture"));
	load_message(true, "fog texture");
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->door),
			"assets/textures/walls/door5.xpm", 2048))
		return (load_message(false, "door texture"));
	load_message(true, "door texture");
	if (!get_image_cub_from_xpm(main_struct, &(main_struct->potion),
			"assets/textures/walls/potion.xpm", 64))
		return (load_message(false, "potion texture"));
	load_message(true, "potion texture");
	if (!create_img_cub(main_struct, &(main_struct->minimap),
			WINDOW_HEIGHT / 3, WINDOW_HEIGHT / 3))
		return (load_message(false, "minimap"));
	load_message(true, "minimap");
	if (!create_img_cub(main_struct, &(main_struct->fuel_bar),
			HUD_WIDTH, HUD_HEIGHT))
		return (load_message(false, "fuel bar"));
	load_message(true, "fuel bar");
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
