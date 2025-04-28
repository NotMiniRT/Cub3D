#include <stdlib.h>

#include "libft.h"
#include "parsing.h"

/**
 * Initializes a new scene structure with NULL values
 * @return Newly allocated scene structure
 */
t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		return (NULL);
	return (scene);
}

/**
 * Frees a color structure and its contents
 * @param color Color structure to free
 */
void	free_color(t_color *color)
{
	if (!color)
		return ;
	if (color->line)
		free(color->line);
	free(color);
}

/**
 * Frees scene structure and all its contents
 * @param scene Scene structure to free
 */
void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_color(scene->floor_color);
	free_color(scene->ceiling_color);
	if (scene->we_texture)
		free(scene->we_texture);
	if (scene->so_texture)
		free(scene->so_texture);
	if (scene->no_texture)
		free(scene->no_texture);
	if (scene->ea_texture)
		free(scene->ea_texture);
	free(scene);
}
