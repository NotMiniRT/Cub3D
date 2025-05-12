#include <unistd.h>

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static int	check_line_integrity(char *line)
{
	int	i;

	i = 0;
	if (line == NULL || line[0] == '\0')
		return (false);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && \
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && \
			line[i] != 'W' && line[i] != 'C' && line[i] != 'D' && \
			line[i] != 'M' && line[i] != '\n')
		{
			ft_dprintf(STDERR_FILENO, "char qui casse: %c\n", line[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	is_empty_line(char *line)
{
	int	i;

	if (line == NULL)
		return (true);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	return (line[i] == '\0');
}

static int	process_scene_line(t_infos *infos, int line_index,
								t_parser_func *parsers, bool *found_element)
{
	char	*line;
	int		element_type;

	line = infos->data->lines[line_index];
	if (is_empty_line(line))
		return (-1);
	element_type = get_element_type(line);
	if (element_type != -1)
	{
		*found_element = true;
		if (!parsers[element_type](infos->scene, line))
		{
			ft_dprintf(STDERR_FILENO, ERR_PARSING_ELEMENT, line);
			return (-2);
		}
	}
	else if (*found_element)
	{
		if (is_scene_complete(infos->scene) && check_line_integrity(line))
			return (line_index);
		return (-2);
	}
	return (-1);
}

static void	scene_complete(t_infos *infos)
{
	if (!is_scene_complete(infos->scene))
	{
		ft_dprintf(STDERR_FILENO, ERR_MISSING_ELEMENT);
		cleanup_parsing(infos);
		exit_error(ERR_SCENE_INVALID);
	}
}

int	check_scene_validity(t_infos *infos)
{
	static t_parser_func	parsers[] = {
		&parse_no_texture, &parse_so_texture,
		&parse_we_texture, &parse_ea_texture,
		&parse_floor_color, &parse_ceiling_color};
	int						i;
	bool					found_element;
	int						result;

	i = 0;
	found_element = false;
	while (infos->data->lines[i])
	{
		result = process_scene_line(infos, i, parsers, &found_element);
		if (result >= 0)
			return (result);
		else if (result == -2)
		{
			cleanup_parsing(infos);
			exit_error(ERR_SCENE_INVALID);
		}
		i++;
	}
	scene_complete(infos);
	return (-1);
}
