#include "map_validation.h"

void	store_collectibles(t_map_data map_data, t_infos *infos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	infos->scene->collectible_count = 0;
	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_collectible(map_data.map[i][j]))
			{
				if (count < 100) // Maximum 100 collectibles
				{
					infos->scene->collectible_positions[count][0] = j;
					infos->scene->collectible_positions[count][1] = i;
					count++;
				}
			}
			j++;
		}
		i++;
	}
	infos->scene->collectible_count = count;
}

void	store_doors(t_map_data map_data, t_infos *infos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	infos->scene->door_count = 0;
	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_door(map_data.map[i][j]))
			{
				if (count < 100) // Maximum 100 doors
				{
					infos->scene->door_positions[count][0] = j;
					infos->scene->door_positions[count][1] = i;
					count++;
				}
			}
			j++;
		}
		i++;
	}
	infos->scene->door_count = count;
}

void	store_monsters(t_map_data map_data, t_infos *infos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	infos->scene->monster_count = 0;
	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_monster(map_data.map[i][j]))
			{
				if (count < 100) // Maximum 100 monsters
				{
					infos->scene->monster_positions[count][0] = j;
					infos->scene->monster_positions[count][1] = i;
					count++;
				}
			}
			j++;
		}
		i++;
	}
	infos->scene->monster_count = count;
}
