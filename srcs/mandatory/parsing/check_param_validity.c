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

void	init_parsing(t_infos *infos, char **av) // faire les retours d'erreurs avec errno ou enlever les autres retour d'erreurs avec errno
{
	infos->data = malloc(sizeof(t_parsing));
	if (infos->data == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		exit(errno);
	}
	infos->scene = malloc(sizeof(t_scene));
	if (infos->scene == NULL)
	{
		free(infos->data);
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		exit(errno);
	}
	init_data(infos, av);
	ft_memset(infos->scene, 0, sizeof(t_scene));
	infos->data->lines = read_all_lines(infos);
	if (infos->data->lines == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		cleanup_parsing(infos);
		exit(errno);
	}
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
