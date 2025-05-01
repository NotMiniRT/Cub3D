#ifndef MAP_STRUCT_VALIDATION_H
# define MAP_STRUCT_VALIDATION_H

# include <stdbool.h>

# include "map_types.h"

bool	check_area_closed(t_map_data map_data);

bool	is_point_closed(t_map_data map_data, t_point p);

#endif
