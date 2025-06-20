/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:47:13 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:47:14 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

bool	check_map_chars(t_infos *infos, int map_start)
{
	int		i;
	int		j;
	char	c;

	i = map_start;
	while (infos->data->lines[i])
	{
		j = 0;
		while (infos->data->lines[i][j])
		{
			c = infos->data->lines[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && \
				c != 'E' && c != 'W' && !ft_isspace(c) && c != '\n')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
