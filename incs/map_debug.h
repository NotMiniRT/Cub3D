#ifndef MAP_DEBUG_H
# define MAP_DEBUG_H

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define RESET		"\033[0m"

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef struct s_map_data	t_map_data;
typedef struct s_infos		t_infos;


void	print_cell_color(char c);
void	debug_print_map(t_map_data map_data);
void	debug_print_map_with_coords(t_map_data map_data);

void	print_debug_steps(const char *message, t_map_data map_data);
void	debug_print_entities(t_infos *infos, int show_flags);

#endif
