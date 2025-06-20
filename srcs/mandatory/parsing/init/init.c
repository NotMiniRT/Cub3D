/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:46:57 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:46:58 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

void	init_data(t_infos *infos, char **av)
{
	infos->data->line = NULL;
	infos->data->count = 0;
	infos->data->capacity = 16;
	infos->data->new_lines = NULL;
	infos->data->lines = malloc(sizeof(char *) * 16);
	if (infos->data->lines == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		cleanup_parsing(infos);
		exit(errno);
	}
	ft_memset(infos->data->lines, 0, sizeof(char *) * 16);
	infos->data->fd = open(av[1], O_RDONLY);
	if (infos->data->fd == -1)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		cleanup_parsing(infos);
		exit(errno);
	}
}

void	init_parsing(t_infos *infos, char **av)
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
	ft_memset(infos->scene, 0, sizeof(t_scene));
	init_data(infos, av);
	infos->data->lines = read_all_lines(infos->data);
	if (infos->data->lines == NULL || errno != 0)
	{
		cleanup_parsing(infos);
		exit(errno);
	}
}
