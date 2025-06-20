/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug_collectibles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:46 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:44:47 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map_debug.h"
#include "map_types.h"
#include "parsing.h"

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
			infos->scene->monster_positions[0],
			infos->scene->monster_positions[1]);
		printf("\n");
	}
}

void	debug_print_entities(t_infos *infos, int show_flags)
{
	if (!DEBUG_MODE)
		return ;
	printf("\n--- DEBUG: ENTITY POSITIONS ---\n");
	debug_print_door(infos, show_flags);
	debug_print_monster(infos, show_flags);
	printf("---------------------------\n\n");
}

void	print_debug_steps(const char *message, t_map_data map_data)
{
	if (DEBUG_MODE)
	{
		printf(DEBUG_SEPARATOR, message);
		debug_print_map(map_data);
	}
}
