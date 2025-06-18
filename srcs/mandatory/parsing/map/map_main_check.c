#include <stdio.h>
#include <stdlib.h>

#include "map_debug.h"
#include "map_processing.h"
#include "map_struct_validation.h"
#include "map_validation.h"
#include "map_types.h"
#include "parsing.h"

static void	validate_map_basics(t_infos *infos, int map_start)
{
	if (map_start < 6 || !infos->data->lines[map_start])
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

void	print_debug_steps(const char *message, t_map_data map_data)
{
	if (DEBUG_MODE)
	{
		printf(DEBUG_SEPARATOR, message);
		debug_print_map(map_data);
	}
}

static void	validate_extended_map(t_infos *infos, t_map_data map_data)
{
	print_debug_steps(DEBUG_INITIAL_MAP, map_data);
	mark_spaces_as_exterior(map_data);
	print_debug_steps(DEBUG_MAP_AFTER_SPACE, map_data);
	if (!check_area_closed(map_data))
	{
		if (DEBUG_MODE)
		{
			printf(DEBUG_UNCLOSED_MAP);
			debug_print_map_with_coords(map_data);
		}
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit(1);
	}
}

static void	validate_player_count(t_infos *infos, t_map_data map_data)
{
	int	player_count;

	player_count = count_players(map_data, infos);
	if (player_count != 1)
	{
		if (DEBUG_MODE)
		{
			printf(DEBUG_PLAYER_COUNT, player_count);
			debug_print_map(map_data);
		}
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
