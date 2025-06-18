#include "map_validation.h"
#include "map_types.h"
#include "parsing.h"

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || \
			c == 'E' || c == 'W' || c == ' ' || c == 'D' || \
			c == 'C' || c == 'M');
}

bool	is_space_or_outside(t_map_data map_data, t_point p)
{
	if (p.y <= 0 || p.y >= map_data.height - 1 || \
		p.x <= 0 || p.x >= map_data.width - 1)
		return (true);
	return (map_data.map[p.y][p.x] == ' ' || map_data.map[p.y][p.x] == 'X');
}

bool	is_door(char c)
{
	return (c == 'D');
}

bool	is_collectible(char c)
{
	return (c == 'C');
}

bool	is_monster(char c)
{
	return (c == 'M');
}
