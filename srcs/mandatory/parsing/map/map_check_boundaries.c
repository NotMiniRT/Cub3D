#include "ft_dprintf.h"
#include "map_validation.h"
#include "map_types.h"
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
