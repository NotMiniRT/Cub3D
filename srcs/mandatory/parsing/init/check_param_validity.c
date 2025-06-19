#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

bool	check_extension(char *map, int fd, char *extension)
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
	if (last_dot == 0 || (last_slash != 0 && last_dot == last_slash + 1) || \
						ft_strcmp(&map[last_dot], extension) != 0)
	{
		close(fd);
		return (false);
	}
	return (true);
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
		if (check_extension(av[1], fd, CUB_FORMAT) == false)
			exit_error(ERR_EXTENSION);
	}
	if (fd != -1)
		close(fd);
}

void	parsing(int ac, char **av, t_infos *infos)
{
	check_param_validity(ac, av);
	init_parsing(infos, av);
	infos->map_start = check_scene_validity(infos);
	check_map_validity(infos, infos->map_start);
}
