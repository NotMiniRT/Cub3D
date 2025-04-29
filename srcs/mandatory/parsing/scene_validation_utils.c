#include "libft.h"
#include "parsing.h"

bool	is_scene_complete(t_scene *scene)
{
	return (scene->floor_color && scene->ceiling_color && \
			scene->we_texture && scene->so_texture && \
			scene->no_texture && scene->ea_texture);
}

int	get_element_type(char *line)
{
	if (!line || !*line)
		return (-1);
	if (ft_strncmp(line, TEXTURE_NO, 2) == 0 && \
		(line[2] == ' ' || ft_isspace_no_nl(line[2]) != 0))
		return (0);
	else if (ft_strncmp(line, TEXTURE_SO, 2) == 0 && \
		(line[2] == ' ' || ft_isspace_no_nl(line[2]) != 0))
		return (1);
	else if (ft_strncmp(line, TEXTURE_WE, 2) == 0 && \
		(line[2] == ' ' || ft_isspace_no_nl(line[2]) != 0))
		return (2);
	else if (ft_strncmp(line, TEXTURE_EA, 2) == 0 && \
		(line[2] == ' ' || ft_isspace_no_nl(line[2]) != 0))
		return (3);
	else if (ft_strncmp(line, COLOR_F, 1) == 0 && \
		(line[1] == ' ' || ft_isspace_no_nl(line[1]) != 0))
		return (4);
	else if (ft_strncmp(line, COLOR_C, 1) == 0 && \
		(line[1] == ' ' || ft_isspace_no_nl(line[1]) != 0))
		return (5);
	return (-1);
}
