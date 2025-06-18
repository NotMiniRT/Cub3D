#include <stdbool.h>

#include "map_types.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || \
			c == 'E' || c == 'W' || c == ' ');
}

bool	is_space_or_outside(t_map_data map_data, t_point p)
{
	if (p.y <= 0 || p.y >= map_data.height - 1 || \
		p.x <= 0 || p.x >= map_data.width - 1)
		return (true);
	return (map_data.map[p.y][p.x] == ' ' || map_data.map[p.y][p.x] == 'X');
}
