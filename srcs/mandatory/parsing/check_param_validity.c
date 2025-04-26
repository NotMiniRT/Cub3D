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

void	init_parsing(t_infos *infos, char **av) // faire les retours d'erreurs avec errno ou enlever les autres retour d'erreurs avec errno
{
	infos->data = malloc(sizeof(t_parsing));
	if (infos->data == NULL)
		exit(97); // changer ca
	infos->scene = malloc(sizeof(t_scene));
	if (infos->scene == NULL)
	{
		free(infos->data);
		exit(98); // changer aussi
	}
	init_data(infos->data, av);
	ft_memset(infos->scene, 0, sizeof(t_scene));
	infos->data->lines = read_all_lines(infos->data);
	if (infos->data->lines == NULL)
	{
		free(infos->data);
		free(infos->scene);
		exit(99); // changer aussi
	}
	// cleanup_parsing(data);
}



void	parsing(int ac, char **av)
{
	t_infos		infos;

	check_param_validity(ac, av);
	ft_memset(&infos, 0, sizeof(t_infos));
	init_parsing(&infos, av);
	check_scene_validity(&infos);
	// check_map_validity(av);
}
