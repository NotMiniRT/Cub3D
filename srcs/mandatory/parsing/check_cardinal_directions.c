#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "parsing.h"
#include "ft_dprintf.h"

bool	parse_no_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->no_texture != NULL)
	{
		ft_dprintf(STDERR_FILENO, ERR_DUPLICATE, TEXTURE_NO);
		return (false);
	}
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
	{
		ft_dprintf(STDERR_FILENO, ERR_DUPLICATE, TEXTURE_SO);
		return (false);
	}
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
	{
		ft_dprintf(STDERR_FILENO, ERR_DUPLICATE, TEXTURE_WE);
		return (false);
	}
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
	{
		ft_dprintf(STDERR_FILENO, ERR_DUPLICATE, TEXTURE_EA);
		return (false);
	}
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
