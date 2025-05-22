#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "map_debug.h"
#include "map_processing.h"
#include "map_struct_validation.h"
#include "map_types.h"
#include "map_validation.h"
#include "parsing.h"

static void	validate_map_basics(t_infos *infos, int map_start)
{
	if (map_start < 6)
	{
		cleanup_parsing(infos);
		exit_error(ERR_NO_MAP);
	}
	if (!infos->data->lines[map_start])
	{
		cleanup_parsing(infos);
		exit_error(ERR_NO_MAP);
	}
	if (!check_map_chars(infos, map_start))
	{
		cleanup_parsing(infos);
		exit_error(ERR_INVALID_CHAR);
	}
}

static void	validate_extended_map(t_infos *infos, t_map_data map_data)
{
	mark_spaces_as_exterior(map_data);
	print_debug_steps(DEBUG_MAP_AFTER_SPACE, map_data);
	if (!check_area_closed(map_data))
	{
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit(EXIT_FAILURE);
	}
	if (!check_doors(map_data, infos))
	{
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit(EXIT_FAILURE);
	}
	if (!are_entities_valid(map_data))
	{
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit(EXIT_FAILURE);
	}
	store_monsters(map_data, infos);
	debug_print_entities(infos, 7);
}

static void	validate_player_count(t_infos *infos, t_map_data map_data)
{
	int	player_count;

	player_count = count_players(map_data, infos);
	if (player_count != 1)
	{
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		if (player_count > 1)
			exit_error(ERR_TOO_MANY_PLAYER);
		else
			exit_error(ERR_NO_PLAYER);
	}
	print_debug_steps(DEBUG_VALID_MAP, map_data);
}

void	check_map_validity(t_infos *infos, int map_start)
{
	t_ext_map	ext_map;
	t_map_data	map_data;
	int			height;
	int			width;

	validate_map_basics(infos, map_start);
	get_map_dimensions(infos, map_start, &height, &width);
	ext_map.height = height;
	ext_map.width = width;
	ext_map.map_start = map_start;
	map_data.map = create_extended_map(infos, &ext_map);
	if (map_data.map == NULL)
	{
		cleanup_parsing(infos);
		exit(EXIT_FAILURE);
	}
	map_data.height = height + 2;
	map_data.width = width + 2;
	validate_extended_map(infos, map_data);
	validate_player_count(infos, map_data);
	free_extended_map(map_data.map, map_data.height);
}
