#ifndef PARSING_H
# define PARSING_H

# define BUFFER_SIZE 1024

# define TEXTURE_NO "NO"
# define TEXTURE_SO "SO"
# define TEXTURE_WE "WE"
# define TEXTURE_EA "EA"
# define COLOR_F "F"
# define COLOR_C "C"

# define ERR_NB_PARAMS "Error: wrong number of parameters.\n"
# define ERR_EXTENSION "Error: wrong file format extension\n"

# define _ERROR "Error: %s\n"

# define CUB_FORMAT ".cub"

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
}	t_infos;

char	**read_all_lines(t_parsing *data);

void	exit_error(char *message);
void	parsing(int ac, char **av);
void	init_data(t_parsing *data, char **av);
void	cleanup_parsing(t_parsing *data);


#define ERR_COLOR_INVALID "Invalid color format\n"
#define ERR_COLOR_RANGE "Color value out of range (0-255)\n"
#define ERR_DUPLICATE "Duplicate element identifier\n"

int		check_scene_validity(t_infos *infos);


#endif
