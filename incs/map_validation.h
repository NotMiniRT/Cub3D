#ifndef MAP_VALIDATION_H
# define MAP_VALIDATION_H

# include <stdbool.h>

# include "map_types.h"
# include "parsing.h"

# define ERR_UNCLOSED_POS "Error\nUnclosed map at [%d,%d]\n"

bool	check_map_chars(t_infos *infos, int map_start);

bool	is_player_or_empty(char c);
bool	is_space_or_outside(t_map_data map_data, t_point p);
bool	is_valid_map_char(char c);

int		count_players(t_map_data map_data, t_infos *infos);

void	check_map_validity(t_infos *infos, int map_start);

#endif
