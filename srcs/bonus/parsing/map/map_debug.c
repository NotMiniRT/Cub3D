/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:48 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:44:49 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map_debug.h"
#include "map_types.h"

void	print_cell_color(char c)
{
	if (c == 'X')
		printf(RED "%c" RESET, c);
	else if (c == '1')
		printf(BLUE "%c" RESET, c);
	else if (c == '0')
		printf(WHITE "%c" RESET, c);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		printf(GREEN "%c" RESET, c);
	else if (c == ' ')
		printf(YELLOW "·" RESET);
	else
		printf(MAGENTA "%c" RESET, c);
}

void	debug_print_map(t_map_data map_data)
{
	int	i;
	int	j;

	printf("\n--- DEBUG: Extended Map (%dx%d) ---\n",
		map_data.height, map_data.width);
	i = 0;
	while (i < map_data.height)
	{
		printf("%2d: ", i);
		j = 0;
		while (j < map_data.width && map_data.map[i][j])
		{
			if (map_data.map[i][j] == ' ')
				printf(YELLOW "·" RESET);
			else if (map_data.map[i][j] == '\n')
				printf(RED "¶" RESET);
			else
				print_cell_color(map_data.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("----------------------------\n\n");
}

static void	print_column_coordinates(int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (j % 10 == 0)
			printf(CYAN "%d" RESET, (j / 10) % 10);
		else
			printf(" ");
		j++;
	}
	printf("\n  ");
	j = 0;
	while (j < width)
	{
		printf(CYAN "%d" RESET, j % 10);
		j++;
	}
	printf("\n");
}

void	debug_print_map_with_coords(t_map_data map_data)
{
	int	i;
	int	j;

	printf("\n--- DEBUG: Extended Map (%dx%d) ---\n  ",
		map_data.height, map_data.width);
	print_column_coordinates(map_data.width);
	i = 0;
	while (i < map_data.height)
	{
		printf(CYAN "%2d" RESET " ", i);
		j = 0;
		while (j < map_data.width)
		{
			print_cell_color(map_data.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("----------------------------\n\n");
}
