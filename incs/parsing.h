#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_scene	t_scene;
typedef bool			(*t_parser_func)(t_scene *scene, char *line);

# define BUFFER_SIZE 1024
# define CLEAR_BUFFER -42

# define TEXTURE_NO	"NO"
# define TEXTURE_SO	"SO"
# define TEXTURE_WE	"WE"
# define TEXTURE_EA	"EA"
# define COLOR_F	"F"
# define COLOR_C	"C"

# define CUB_FORMAT ".cub"
# define XPM_FORMAT ".xpm"

# define _ERROR		"Error: %s\n"

# define ERR_NB_PARAMS			"Error\nWrong number of parameters\n"
# define ERR_EXTENSION			"Error\nWrong file format extension\n"

# define ERR_COLOR_INVALID		"Invalid color format\n"
# define ERR_DUPLICATE			"Error\nDuplicate %s identifier\n"

# define ERR_INCOMPLETE_SCENE	"Error\nScene incomplete before map start\n"
# define ERR_INVALID_CHAR		"Error\nInvalid character encountered\n"
# define ERR_MISSING_ELEMENT	"Error\nMissing required scene elements\n"
# define ERR_NO_MAP				"Error\nNo map in file"
# define ERR_PARSING_ELEMENT	"Error\nParsing element: %s\n"
# define ERR_SCENE_INVALID		"Error\nInvalid scene configuration\n"
# define ERR_TOO_MANY_PLAYER	"Error\nToo many players"

# define DEBUG_INITIAL_MAP		"INITIAL MAP"
# define DEBUG_MAP_AFTER_SPACE	"MAP AFTER SPACES INCLUSING"
# define DEBUG_PLAYER_COUNT		"\n--- ERROR: INVALID NUMBER OF PLAYER (%d) ---\n"
# define DEBUG_SEPARATOR		"\n--- %s ---\n"
# define DEBUG_UNCLOSED_MAP		"\n--- ERROR: UNCLOSED MAP ---\n"
# define DEBUG_VALID_MAP		"MAP SUCCESSFULLY VALIDATED"

typedef struct s_color
{
	char			*line;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_scene
{
	t_color	*floor_color;
	t_color	*ceiling_color;
	char	*we_texture;
	char	*so_texture;
	char	*no_texture;
	char	*ea_texture;
	int		pos[3];
	int		collectible_count;
	int		door_count;
	int		monster_count;
	int		collectible_positions[100][2]; // Storing up to 100 collectibles (x,y)
	int		door_positions[100][2];        // Storing up to 100 doors (x,y)
	int		monster_positions[100][2];     // Storing up to 100 monsters (x,y)
}	t_scene;

typedef struct s_parsing
{
	size_t	count;
	size_t	capacity;
	int		fd;
	char	*line;
	char	**new_lines;
	char	**lines;
}	t_parsing;

typedef struct s_infos
{
	t_parsing	*data;
	t_scene		*scene;
	int			map_start;
}	t_infos;

char	**read_all_lines(t_parsing *data);
char	**clear_read_lines(t_parsing *data);

void	exit_error(char *message);
void	parsing(int ac, char **av, t_infos *infos);
void	init_data(t_infos *infos, char **av);
void	cleanup_parsing(t_infos *infos);
char	*read_line(int fd);

char	*extract_line(char **buffer);
char	*join_and_free(char *s1, char *s2);
bool	read_line_check(int fd, char *buffer);

void	free_array(char **array);
void	free_scene(t_scene *scene);

/* map parsing*/
void	free_extended_map(char **extended_map, int height);

bool	check_extension(char *map, int fd, char *extension);

/* -------------------------------------------------------------------------- */

void	init_data(t_infos *infos, char **av);
void	init_parsing(t_infos *infos, char **av);

int		check_scene_validity(t_infos *infos);

bool	parse_ceiling_color(t_scene *scene, char *line);
bool	parse_floor_color(t_scene *scene, char *line);

bool	parse_ea_texture(t_scene *scene, char *line);
bool	parse_no_texture(t_scene *scene, char *line);
bool	parse_so_texture(t_scene *scene, char *line);
bool	parse_we_texture(t_scene *scene, char *line);

bool	is_texture_valid(char *path);
bool	is_scene_complete(t_scene *scene);

char	*extract_texture_path(char *line, int id_len);

int		get_element_type(char *line);

void	check_map_validity(t_infos *infos, int map_start);

#endif
