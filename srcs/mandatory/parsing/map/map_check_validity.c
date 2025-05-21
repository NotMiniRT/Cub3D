#include <stdio.h>

#include "libft.h"
#include "map_validation.h"
#include "parsing.h"
#include "map_debug.h"

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
