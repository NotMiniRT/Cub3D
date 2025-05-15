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

const int	g_debug_mode = DEBUG_MODE;

static void	debug_print_entities(t_infos *infos, int show_flags)
{
	int	i;

	if (!g_debug_mode)
		return ;
	printf("\n--- DEBUG: ENTITY POSITIONS ---\n");
	if ((show_flags & 1) && infos->scene->collectible_count > 0)
	{
		printf(GREEN "Collectibles (%d):" RESET "\n", infos->scene->collectible_count);
		for (i = 0; i < infos->scene->collectible_count; i++)
		{
			printf("  C[%d]: x=%d, y=%d\n",
				   i,
				   infos->scene->collectible_positions[i][0],
				   infos->scene->collectible_positions[i][1]);
		}
		printf("\n");
	}
	if ((show_flags & 2) && infos->scene->door_count > 0)
	{
		printf(BLUE "Doors (%d):" RESET "\n", infos->scene->door_count);
		for (i = 0; i < infos->scene->door_count; i++)
		{
			printf("  D[%d]: x=%d, y=%d, value=%d\n",
				   i,
				   infos->scene->door_positions[i][0],
				   infos->scene->door_positions[i][1],
				   infos->scene->door_positions[i][2]);
		}
		printf("\n");
	}
	if ((show_flags & 4) && infos->scene->monster_count > 0)
	{
		printf(RED "Monsters (%d):" RESET "\n", infos->scene->monster_count);
		for (i = 0; i < infos->scene->monster_count; i++)
		{
			printf("  M[%d]: x=%d, y=%d\n",
				   i,
				   infos->scene->monster_positions[i][0],
				   infos->scene->monster_positions[i][1]);
		}
		printf("\n");
	}
	printf("---------------------------\n\n");
}

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

static void	print_debug_steps(const char *message, t_map_data map_data)
{
	if (g_debug_mode)
	{
		printf(DEBUG_SEPARATOR, message);
		debug_print_map(map_data);
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
		exit(1);
	}
	if (!check_doors(map_data))
	{
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit(1);
	}
	if (!are_entities_valid(map_data))
	{
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit(1);
	}
	store_collectibles(map_data, infos);
	store_doors(map_data, infos);
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
		exit(1);
	}
	map_data.height = height + 2;
	map_data.width = width + 2;
	validate_extended_map(infos, map_data);
	validate_player_count(infos, map_data);
	free_extended_map(map_data.map, map_data.height);
}
