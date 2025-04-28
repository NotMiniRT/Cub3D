#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static void	check_extension(char *map, int fd)
{
	size_t	i;
	size_t	last_dot;
	size_t	last_slash;

	i = 0;
	last_dot = 0;
	last_slash = 0;
	while (map && map[i])
	{
		if (map[i] == '/')
			last_slash = i;
		else if (map[i] == '.')
			last_dot = i;
		i++;
	}
	if (last_dot == 0 || (last_slash != 0 && last_dot == last_slash + 1) ||
        ft_strcmp(&map[last_dot], CUB_FORMAT) != 0)
	{
		close(fd);
		exit_error(ERR_EXTENSION);
	}
}

void	check_param_validity(int ac, char **av)
{
	int	fd;

	fd = -1;
	if (ac != 2)
		exit_error(ERR_NB_PARAMS);
	else
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
			exit(errno);
		}
		check_extension(av[1], fd);
	}
	if (fd != -1)
		close(fd);
}

void	parsing(int ac, char **av)
{
	t_infos	infos;

	check_param_validity(ac, av);
	ft_memset(&infos, 0, sizeof(t_infos));
	init_parsing(&infos, av);
	cleanup_parsing(&infos);
	exit(1);
	check_scene_validity(&infos);
	// check_map_validity(av);
}
