#ifndef PARSING_H
# define PARSING_H

# define ERR_NB_PARAMS "Error: wrong number of parameters.\n"
# define ERR_EXTENSION "Error: wrong file format extension\n"

# define _ERROR "Error: %s\n"

# define CUB_FORMAT ".cub"

void	exit_error(char *message);
void	parsing(int ac, char **av);

#endif
