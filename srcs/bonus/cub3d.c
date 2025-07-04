/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:46:11 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:46:12 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "common.h"
#include "display_b.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "main_struct_b.h"
#include "parsing.h"
#include "sound.h"
#include "structs_b.h"

int	main(int ac, char **av)
{
	t_main_struct	main_struct;
	t_infos			infos;

	ft_memset(&main_struct, 0, sizeof(t_main_struct));
	ft_memset(&infos, 0, sizeof(t_infos));
	parsing(ac, av, &infos);
	if (!start_display(&main_struct, &infos))
		ft_dprintf(STDERR_FILENO, ERROR_EXTERNAL);
	free_main_struct_first_part(&main_struct);
	cleanup_parsing(&infos);
	cleanup_sound(&main_struct);
	return (EXIT_SUCCESS);
}
