#ifndef MAP_VALIDATION_H
# define MAP_VALIDATION_H

# include <stdbool.h>

typedef struct s_infos		t_infos;
typedef struct s_map_data	t_map_data;
typedef struct s_point		t_point;

# define ERR_UNCLOSED_POS "Error\nUnclosed map at [%d,%d]\n"
# define ERR_INVALID_DOOR "Error\nInvalid door placement at [%d,%d]\n"

bool	check_map_chars(t_infos *infos, int map_start);

bool	is_player_or_empty(char c);
bool	is_space_or_outside(t_map_data map_data, t_point p);
bool	is_valid_map_char(char c);
bool	is_collectible(char c);
bool	is_door(char c);
bool	is_monster(char c);

bool	check_doors(t_map_data map_data, t_infos *infos);
bool	are_entities_valid(t_map_data map_data);

int		count_players(t_map_data map_data, t_infos *infos);

void	store_door(t_map_data map_data, int i, int j, t_infos *infos);

void	store_monsters(t_map_data map_data, t_infos *infos);

void	store_item(t_map_data map_data, t_infos *infos);

void	check_map_validity(t_infos *infos, int map_start);

#endif
