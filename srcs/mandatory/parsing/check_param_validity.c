#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "common.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static void	check_extension(char *map, int fd)
{
	size_t	i;

	i = 0;
	while (map && map[i])
		i++;
	if (i < 4 || ft_strcmp(&map[i - 4], CUB_FORMAT) != 0)
	{
		close(fd);
		exit_error(ERR_EXTENSION);
	}
}

void	check_param_validity(int ac, char **av)
{
	int	fd;

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
	close(fd);
}

void	init_parsing(t_parsing *data, char **av)
{
	init_data(data, av);
	read_all_lines(data);
	// cleanup_parsing(data);
}

void	parsing(int ac, char **av)
{
	t_parsing	data;

	check_param_validity(ac, av);
	init_parsing(&data, av);
	// check_scene_validity(av);
	// check_map_validity(av);
}
