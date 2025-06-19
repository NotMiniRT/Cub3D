#include <unistd.h>

#include "ft_dprintf.h"
#include "map_types.h"
#include "map_validation.h"
#include "parsing.h"

bool	is_point_closed(t_map_data map_data, t_point p)
{
	t_point	check;

	check.y = p.y - 1;
	check.x = p.x;
	if (is_space_or_outside(map_data, check))
		return (false);
	check.y = p.y + 1;
	if (is_space_or_outside(map_data, check))
		return (false);
	check.y = p.y;
	check.x = p.x - 1;
	if (is_space_or_outside(map_data, check))
		return (false);
	check.x = p.x + 1;
	if (is_space_or_outside(map_data, check))
		return (false);
	return (true);
}

bool	are_entities_valid(t_map_data map_data)
{
	int		i;
	int		j;
	t_point	p;

	i = 0;
	while (++i < map_data.height - 1)
	{
		j = 0;
		while (++j < map_data.width - 1)
		{
			if (is_collectible(map_data.map[i][j]) || \
				is_monster(map_data.map[i][j]))
			{
				p.y = i;
				p.x = j;
				if (!is_point_closed(map_data, p))
				{
					ft_dprintf(STDERR_FILENO, ERR_ENTITY, i, j);
					return (false);
				}
			}
		}
	}
	return (true);
}
