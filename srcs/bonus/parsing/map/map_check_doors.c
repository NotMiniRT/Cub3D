/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_doors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:36 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:44:37 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_dprintf.h"
#include "map_types.h"
#include "map_validation.h"
#include "parsing.h"

static bool	is_door_valid(t_map_data map_data, int i, int j)
{
	bool	horizontal_valid;
	bool	vertical_valid;

	if (i <= 0 || i >= map_data.height - 1 || j <= 0 || j >= map_data.width - 1)
		return (false);
	horizontal_valid = (map_data.map[i][j - 1] == '1' && \
						map_data.map[i][j + 1] == '1');
	vertical_valid = (map_data.map[i - 1][j] == '1' && \
						map_data.map[i + 1][j] == '1');
	return (horizontal_valid || vertical_valid);
}

bool	check_doors(t_map_data map_data, t_infos *infos)
{
	int	i;
	int	j;

	i = 0;
	infos->scene->door_count = 0;
	while (++i < map_data.height - 1)
	{
		j = 0;
		while (++j < map_data.width - 1)
		{
			if (is_door(map_data.map[i][j]))
			{
				if (!is_door_valid(map_data, i, j))
				{
					ft_dprintf(STDERR_FILENO, ERR_INVALID_DOOR, i, j);
					return (false);
				}
				store_door(map_data, i, j, infos);
			}
		}
	}
	return (true);
}
