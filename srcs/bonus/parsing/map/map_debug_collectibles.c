#include <stdio.h>

#include "map_debug.h"
#include "map_validation.h"
#include "parsing.h"

const int	g_debug_mode = DEBUG_MODE;

static void	debug_print_door(t_infos *infos, int show_flags)
{
	int	i;

	i = 0;
	if ((show_flags & 2) && infos->scene->door_count > 0)
	{
		printf(BLUE "Doors (%d):" RESET "\n", infos->scene->door_count);
		while (i < infos->scene->door_count)
		{
			printf("\tD[%d]: x=%d, y=%d, value=%d, direction=%d\n",
				i,
				infos->scene->door_positions[i][0],
				infos->scene->door_positions[i][1],
				infos->scene->door_positions[i][2],
				infos->scene->door_positions[i][3]);
			i++;
		}
		printf("\n");
	}
}

static void	debug_print_monster(t_infos *infos, int show_flags)
{
	int	i;

	i = 0;
	if ((show_flags & 4) && infos->scene->monster_count > 0)
	{
		printf(RED "Monsters (%d):" RESET "\n", infos->scene->monster_count);
		printf("\tM[%d]: x=%d, y=%d\n",
			i,
			infos->scene->monster_positions[i][0],
			infos->scene->monster_positions[i][1]);
		printf("\n");
	}
}

void	debug_print_entities(t_infos *infos, int show_flags)
{
	if (!g_debug_mode)
		return ;
	printf("\n--- DEBUG: ENTITY POSITIONS ---\n");
	debug_print_door(infos, show_flags);
	debug_print_monster(infos, show_flags);
	printf("---------------------------\n\n");
}

void	print_debug_steps(const char *message, t_map_data map_data)
{
	if (g_debug_mode)
	{
		printf(DEBUG_SEPARATOR, message);
		debug_print_map(map_data);
	}
}
