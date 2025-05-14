#include <stdio.h>
#include "map_validation.h"

int	count_collectibles(t_map_data map_data)
{
	int	i;
	int	j;
	int	collectible_count;

	collectible_count = 0;
	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_collectible(map_data.map[i][j]))
				collectible_count++;
			j++;
		}
		i++;
	}
	return (collectible_count);
}

int	count_doors(t_map_data map_data)
{
	int	i;
	int	j;
	int	door_count;

	door_count = 0;
	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_door(map_data.map[i][j]))
				door_count++;
			j++;
		}
		i++;
	}
	return (door_count);
}

int	count_monsters(t_map_data map_data)
{
	int	i;
	int	j;
	int	monster_count;

	monster_count = 0;
	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_monster(map_data.map[i][j]))
				monster_count++;
			j++;
		}
		i++;
	}
	return (monster_count);
}
