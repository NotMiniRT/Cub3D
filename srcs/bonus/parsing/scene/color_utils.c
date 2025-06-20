/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:04 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:45:06 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

bool	is_valid_color_component(char *str, unsigned char *component)
{
	short	value;
	int		i;

	i = 0;
	while (str[i] && ft_isspace_no_nl(str[i]))
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (false);
	value = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (false);
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] != '\n')
		return (false);
	*component = (unsigned char)value;
	return (true);
}

bool	parse_color_components(char *line, t_color_parse *color)
{
	char	**components;
	bool	result;
	int		i;

	i = 1;
	while (line[i] && ft_isspace_no_nl(line[i]))
		i++;
	components = ft_split(&line[i], ',');
	if (!components || !components[0] || !components[1]
		|| !components[2] || components[3])
	{
		if (components)
			free_array(components);
		return (false);
	}
	result = is_valid_color_component(components[0], &color->r) && \
				is_valid_color_component(components[1], &color->g) && \
				is_valid_color_component(components[2], &color->b);
	free_array(components);
	return (result);
}

bool	parse_floor_color(t_scene *scene, char *line)
{
	t_color_parse	*color;

	if (scene->floor_color)
	{
		ft_dprintf(STDERR_FILENO, ERR_DUPLICATE, COLOR_F);
		return (false);
	}
	color = malloc(sizeof(t_color_parse));
	if (color == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		return (false);
	}
	color->line = ft_strdup(line);
	if (color->line == NULL || parse_color_components(line, color) == false)
	{
		if (color->line != NULL)
			free(color->line);
		free(color);
		return (false);
	}
	scene->floor_color = color;
	return (true);
}

bool	parse_ceiling_color(t_scene *scene, char *line)
{
	t_color_parse	*color;

	if (scene->ceiling_color)
		return (false);
	color = malloc(sizeof(t_color_parse));
	if (color == NULL)
	{
		ft_dprintf(STDERR_FILENO, _ERROR, strerror(errno));
		return (false);
	}
	color->line = ft_strdup(line);
	if (color->line == NULL || parse_color_components(line, color) == false)
	{
		if (color->line != NULL)
			free(color->line);
		free(color);
		return (false);
	}
	scene->ceiling_color = color;
	return (true);
}
