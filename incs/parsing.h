#ifndef PARSING_H
# define PARSING_H

# define BUFFER_SIZE 1024

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


char	**read_all_lines(char **av);

void	exit_error(char *message);
void	parsing(int ac, char **av);
void	init_data(t_parsing *data, char **av);


#endif
