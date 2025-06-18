#include "map_validation.h"
#include "parsing.h"
#include "map_types.h"

static bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_player_or_empty(char c)
{
	return (c == '0' || is_player(c) || c == 'C' || c == 'M');
}

int	count_players(t_map_data map_data, t_infos *infos)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_player(map_data.map[i][j]))
			{
				player_count++;
				infos->scene->pos[0] = j;
				infos->scene->pos[1] = i;
				infos->scene->pos[2] = map_data.map[i][j];
			}
			j++;
		}
		i++;
	}
	return (player_count);
}
