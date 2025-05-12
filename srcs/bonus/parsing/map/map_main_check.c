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

int	g_debug_mode = 1;

static void	validate_map_basics(t_infos *infos, int map_start)
{
	if (map_start < 6)
	{
		cleanup_parsing(infos);
		exit_error("Error\nMap invalide (pas de map)");
	}
	if (!infos->data->lines[map_start])
	{
		cleanup_parsing(infos);
		exit_error("Error\nPas de map");
	}
	if (!check_map_chars(infos, map_start))
	{
		cleanup_parsing(infos);
		exit_error("Error\nCaractère invalide dans la map");
	}
}

static void	print_debug_steps(const char *message, t_map_data map_data)
{
	if (g_debug_mode)
	{
		printf("\n--- %s ---\n", message);
		debug_print_map(map_data);
	}
}

static void	validate_extended_map(t_infos *infos, t_map_data map_data)
{
	print_debug_steps("CARTE INITIALE", map_data);
	mark_spaces_as_exterior(map_data);
	print_debug_steps("APRÈS MARQUAGE DES ESPACES", map_data);
	if (!check_area_closed(map_data))
	{
		if (g_debug_mode)
		{
			printf("\n--- ERREUR: CARTE NON FERMÉE ---\n");
			debug_print_map_with_coords(map_data);
		}
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit_error("Error\nMap pas fermee");
	}
}

static void	validate_player_count(t_infos *infos, t_map_data map_data)
{
	int	player_count;

	player_count = count_players(map_data, infos);
	if (player_count != 1)
	{
		if (g_debug_mode)
		{
			printf("\n--- ERREUR: NOMBRE DE JOUEURS INVALIDE (%d) ---\n",
				player_count);
			debug_print_map(map_data);
		}
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit_error("Error\nTrop de joueurs");
	}
	print_debug_steps("CARTE VALIDÉE AVEC SUCCÈS", map_data);
}

static void validate_doors(t_infos *infos, t_map_data map_data)
{
	if (!check_doors(map_data))
	{
		if (g_debug_mode)
		{
			printf("\n--- ERREUR: PLACEMENT DE PORTE INVALIDE ---\n");
			debug_print_map_with_coords(map_data);
		}
		free_extended_map(map_data.map, map_data.height);
		cleanup_parsing(infos);
		exit_error("Error\nPlacement de porte invalide");
	}
}

static void count_entities(t_map_data map_data)
{
	int collectibles = count_collectibles(map_data);
	int doors = count_doors(map_data);
	int monsters = count_monsters(map_data);

	if (g_debug_mode)
	{
		printf("\n--- ENTITÉS TROUVÉES ---\n");
		printf("Collectibles: %d\n", collectibles);
		printf("Portes: %d\n", doors);
		printf("Monstres: %d\n", monsters);
	}
}

void check_map_validity(t_infos *infos, int map_start)
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
	if (!map_data.map)
	{
		cleanup_parsing(infos);
		exit_error("Error\nMalloc");
	}
	map_data.height = height + 2;
	map_data.width = width + 2;
	validate_extended_map(infos, map_data);
	validate_player_count(infos, map_data);
	validate_doors(infos, map_data);
	count_entities(map_data);
	
	// Store entity positions in the scene
	store_collectibles(map_data, infos);
	store_doors(map_data, infos);
	store_monsters(map_data, infos);
	
	print_debug_steps("CARTE VALIDÉE AVEC SUCCÈS", map_data);
	free_extended_map(map_data.map, map_data.height);
}
