#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "parsing.h"
#include "libft.h"

/* ligne 27 : pas sur de vouloir laisser ca non plus */
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

/* ligne 43 : (line[i] == ' ' || line[i] == '\t')*/
bool	parse_color_components(char *line, t_color *color)
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
	t_color	*color;

	if (scene->floor_color)
	{
		ft_dprintf(STDERR_FILENO, ERR_DUPLICATE, COLOR_F);
		return (false);
	}
	color = malloc(sizeof(t_color));
	if (color == NULL)
		return (false);
	color->line = ft_strdup(line);
	if (color->line == NULL)
	{
		free(color);
		return (false);
	}
	if (parse_color_components(line, color) == false)
	{
		free(color->line);
		free(color);
		return (false);
	}
	scene->floor_color = color;
	return (true);
}

/* errno plus tard */
bool	parse_ceiling_color(t_scene *scene, char *line)
{
	t_color	*color;

	if (scene->ceiling_color)
	{
		ft_dprintf(STDERR_FILENO, ERR_DUPLICATE, COLOR_C);
		return (false);
	}
	color = malloc(sizeof(t_color));
	if (color == NULL)
		return (false);
	color->line = ft_strdup(line);
	if (color->line == NULL)
	{
		free(color);
		return (false);
	}
	if (parse_color_components(line, color) == false)
	{
		free(color->line);
		free(color);
		return (false);
	}
	scene->ceiling_color = color;
	return (true);
}
