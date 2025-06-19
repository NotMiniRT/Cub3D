#include <stdlib.h>

#include "parsing.h"

bool	parse_no_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->no_texture != NULL)
		return (false);
	path = extract_texture_path(line, 2);
	if (path == NULL || is_texture_valid(path) == false)
	{
		if (path)
			free(path);
		return (false);
	}
	scene->no_texture = path;
	return (true);
}

bool	parse_so_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->so_texture != NULL)
		return (false);
	path = extract_texture_path(line, 2);
	if (path == NULL || is_texture_valid(path) == false)
	{
		if (path)
			free(path);
		return (false);
	}
	scene->so_texture = path;
	return (true);
}

bool	parse_we_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->we_texture != NULL)
		return (false);
	path = extract_texture_path(line, 2);
	if (path == NULL || is_texture_valid(path) == false)
	{
		if (path)
			free(path);
		return (false);
	}
	scene->we_texture = path;
	return (true);
}

bool	parse_ea_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->ea_texture != NULL)
		return (false);
	path = extract_texture_path(line, 2);
	if (path == NULL || is_texture_valid(path) == false)
	{
		if (path)
			free(path);
		return (false);
	}
	scene->ea_texture = path;
	return (true);
}
