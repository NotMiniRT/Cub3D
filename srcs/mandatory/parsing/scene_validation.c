#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "parsing.h"
#include "libft.h"
#include "ft_dprintf.h"

// External function declarations
extern bool	is_scene_complete(t_scene *scene);
extern int	get_element_type(char *line);
extern void	init_parsers(t_parser_func *parsers);

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

/**
 * Checks the validity of the scene configuration
 * @param infos Structure containing scene and parsing data
 * @return index to start checking the map if valid, -1 otherwise
 */
int	check_scene_validity(t_infos *infos)
{
	t_parser_func	parsers[6];
	int				i;
	int				element_type;
	bool			found_element;

	init_parsers(parsers);
	i = 0;
	found_element = false;
	while (infos->data->lines[i])
	{
		if (!is_empty_line(infos->data->lines[i]))
		{
			element_type = get_element_type(infos->data->lines[i]);
			if (element_type != -1)
			{
				found_element = true;
				if (!parsers[element_type](infos->scene, infos->data->lines[i]))
				{
					ft_dprintf(STDERR_FILENO, ERR_PARSING_ELEMENT,
						infos->data->lines[i]);
					cleanup_parsing(infos);
					exit_error(ERR_SCENE_INVALID);
				}
			}
			else if (found_element)
			{
				if (is_scene_complete(infos->scene))
					return (i);
				else
				{
					ft_dprintf(STDERR_FILENO, ERR_INCOMPLETE_SCENE);
					cleanup_parsing(infos);
					exit_error(ERR_SCENE_INVALID);
				}
			}
		}
		i++;
	}
	if (!is_scene_complete(infos->scene))
	{
		ft_dprintf(STDERR_FILENO, ERR_MISSING_ELEMENT);
		cleanup_parsing(infos);
		exit_error(ERR_SCENE_INVALID);
	}
	return (-1);
}
