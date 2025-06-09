#include "map_validation.h"
#include "parsing.h"

void	store_door(t_map_data map_data, int i, int j, t_infos *infos)
{
	int		count;
	bool	horizontal;
	bool	vertical;

	count = infos->scene->door_count;
	if (count >= 100)
		return ;
	horizontal = (map_data.map[i][j - 1] == '1' && \
				map_data.map[i][j + 1] == '1');
	vertical = (map_data.map[i - 1][j] == '1' && \
				map_data.map[i + 1][j] == '1');
	infos->scene->door_positions[count][0] = j;
	infos->scene->door_positions[count][1] = i;
	infos->scene->door_positions[count][2] = 100;
	if (horizontal && vertical)
		infos->scene->door_positions[count][3] = ENCLOSED;
	else if (vertical)
		infos->scene->door_positions[count][3] = VERTICAL;
	else
		infos->scene->door_positions[count][3] = HORIZONTAL;
	infos->scene->door_count++;
}

void	store_monsters(t_map_data map_data, t_infos *infos)
{
	int	i;
	int	j;

	i = 0;
	infos->scene->monster_count = 0;
	while (++i < map_data.height - 1)
	{
		j = 0;
		while (++j < map_data.width - 1)
		{
			if (is_monster(map_data.map[i][j]))
			{
				infos->scene->monster_count = infos->scene->monster_count + 1;
				infos->scene->monster_positions[0][0] = j;
				infos->scene->monster_positions[0][1] = i;
			}
			if (infos->scene->monster_count > 1)
			{
				free_extended_map(map_data.map, map_data.height);
				cleanup_parsing(infos);
				exit_error(ERR_NB_MONSTER);
			}
		}
	}
}

void	store_item(t_map_data map_data, t_infos *infos)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	infos->scene->collectible_count = 0;
	while (++i < map_data.height - 1)
	{
		j = 0;
		while (++j < map_data.width - 1)
		{
			if (is_collectible(map_data.map[i][j]))
			{
				infos->scene->collectible_positions[count][0] = j;
				infos->scene->collectible_positions[count][1] = i;
				infos->scene->collectible_positions[count][2] = 1;
				count++;
			}
		}
	}
	infos->scene->collectible_count = count;
}