#include <unistd.h>

#include "ft_dprintf.h"
#include "map_struct_validation.h"
#include "map_validation.h"
#include "map_types.h"
#include "parsing.h"

static bool	is_vulnerable_point(t_map_data map_data, int i, int j)
{
	t_point	p;

	if (!is_player_or_empty(map_data.map[i][j]))
		return (false);
	p.y = i;
	p.x = j;
	return (!is_point_closed(map_data, p));
}

bool	check_area_closed(t_map_data map_data)
{
	int	i;
	int	j;

	i = 1;
	while (i < map_data.height - 1)
	{
		j = 1;
		while (j < map_data.width - 1)
		{
			if (is_vulnerable_point(map_data, i, j))
			{
				ft_dprintf(STDERR_FILENO, ERR_UNCLOSED_POS, i, j);
				return (false);
			}
			++j;
		}
		++i;
	}
	return (true);
}
