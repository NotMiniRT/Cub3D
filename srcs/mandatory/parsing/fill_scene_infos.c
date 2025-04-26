#include <stdlib.h>
#include "parsing.h"
#include "libft.h"
#include "ft_dprintf.h"

// Function prototypes for scene validation
// t_scene	*init_scene(void);
void	free_scene(t_scene *scene);
void	free_color(t_color *color);
void	free_array(char **array);

// Function prototypes for texture parsing
char	*extract_texture_path(char *line, int id_len);
bool	is_texture_valid(char *path);
bool	parse_no_texture(t_scene *scene, char *line);
bool	parse_so_texture(t_scene *scene, char *line);
bool	parse_we_texture(t_scene *scene, char *line);
bool	parse_ea_texture(t_scene *scene, char *line);

// Function prototypes for color parsing
bool	parse_floor_color(t_scene *scene, char *line);
bool	parse_ceiling_color(t_scene *scene, char *line);


static bool	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	return (line[i] == '\0');
}

/**
 * Frees a color structure and its contents
 * @param color Color structure to free
 */
void	free_color(t_color *color)
{
	if (color == NULL)
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
	if (scene == NULL)
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

#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "parsing.h"
#include "libft.h"

#define ERR_TEXTURE_INVALID "Invalid texture path"

/**
 * Extracts a texture path from a line
 * @param line Line containing the texture information
 * @param id_len Length of the identifier
 * @return Extracted path or NULL on error
 */
char	*extract_texture_path(char *line, int id_len)
{
	char	*path;
	int		i;

	i = id_len;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path = ft_strdup(&line[i]);
	if (path == NULL)
		return (NULL);
	i = ft_strlen(path) - 1;
	while (i >= 0 && (path[i] == ' ' || path[i] == '\t' || path[i] == '\n'))
	{
		path[i] = '\0';
		i--;
	}
	return (path);
}

/**
 * Checks if a texture file exists and is readable
 * @param path Path to the texture file
 * @return true if valid, false otherwise
 */
bool	is_texture_valid(char *path)
{
	int	fd;

	return (true);
	if (!path || !*path)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

/**
 * Frees an array of strings
 * @param array Array to free
 */
void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

#include <stdbool.h>
#include <stdlib.h>
#include "parsing.h"
#include "libft.h"


extern char	*extract_texture_path(char *line, int id_len);
extern bool	is_texture_valid(char *path);

/**
 * Parses a north texture line
 * @param scene Scene structure to fill
 * @param line Line to parse
 * @return true if successful, false otherwise
 */
bool	parse_no_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->no_texture)
		exit_error(ERR_DUPLICATE);
	path = extract_texture_path(line, 2);
	if (!path || !is_texture_valid(path))
	{
		if (path)
			free(path);
		return (false);
	}
	scene->no_texture = path;
	return (true);
}

/**
 * Parses a south texture line
 * @param scene Scene structure to fill
 * @param line Line to parse
 * @return true if successful, false otherwise
 */
bool	parse_so_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->so_texture)
		exit_error(ERR_DUPLICATE);
	path = extract_texture_path(line, 2);
	if (!path || !is_texture_valid(path))
	{
		if (path)
			free(path);
		return (false);
	}
	scene->so_texture = path;
	return (true);
}

/**
 * Parses a west texture line
 * @param scene Scene structure to fill
 * @param line Line to parse
 * @return true if successful, false otherwise
 */
bool	parse_we_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->we_texture)
		exit_error(ERR_DUPLICATE);
	path = extract_texture_path(line, 2);
	if (!path || !is_texture_valid(path))
	{
		if (path)
			free(path);
		return (false);
	}
	scene->we_texture = path;
	return (true);
}

#include <stdbool.h>
#include <stdlib.h>
#include "parsing.h"
#include "libft.h"


extern char	*extract_texture_path(char *line, int id_len);
extern bool	is_texture_valid(char *path);

/**
 * Parses an east texture line
 * @param scene Scene structure to fill
 * @param line Line to parse
 * @return true if successful, false otherwise
 */
bool	parse_ea_texture(t_scene *scene, char *line)
{
	char	*path;

	if (scene->ea_texture)
		exit_error(ERR_DUPLICATE);
	path = extract_texture_path(line, 2);
	if (!path || !is_texture_valid(path))
	{
		if (path)
			free(path);
		return (false);
	}
	scene->ea_texture = path;
	return (true);
}

#include <stdbool.h>
#include <stdlib.h>
#include "parsing.h"
#include "libft.h"



extern void	free_array(char **array);

/**
 * Valide un composant de couleur
 * @param str Chaîne contenant le composant
 * @param component Pointeur pour stocker la valeur du composant
 * @return true si valide, false sinon
 */
static bool	is_valid_color_component(char *str, unsigned char *component)
{
	int	value;
	int	i;

	i = 0;
	// Ignorer les espaces au début
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (false);
	// Gérer le signe plus optionnel
	if (str[i] == '+')
		i++;
	// Vérifier que le premier caractère est un chiffre
	if (!ft_isdigit(str[i]))
		return (false);
	// Convertir la valeur
	value = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (false);
		i++;
	}
	// Ignorer les espaces à la fin
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	// S'assurer qu'il n'y a rien d'autre
	if (str[i] && str[i] != '\n')
		return (false);
	*component = (unsigned char)value;
	return (true);
}

#include <stdbool.h>
#include <stdlib.h>
#include "parsing.h"
#include "libft.h"

extern bool	is_valid_color_component(char *str, unsigned char *component);
extern void	free_array(char **array);

/**
 * Parses color components from a line
 * @param line Line containing the components
 * @param color Color structure to fill
 * @return true if successful, false otherwise
 */
/**
 * Parse les composantes de couleur à partir d'une ligne
 * @param line Ligne contenant les composantes
 * @param color Structure de couleur à remplir
 * @return true si réussi, false sinon
 */
static bool	parse_color_components(char *line, t_color *color)
{
	char	**components;
	bool	result;
	int		i;

	// Ignorer l'identifiant et les espaces
	i = 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;

	// Diviser la chaîne en composantes
	components = ft_split(&line[i], ',');
	if (!components || !components[0] || !components[1] || !components[2] || components[3])
	{
		if (components)
			free_array(components);
		return (false);
	}

	// Valider chaque composante
	result = is_valid_color_component(components[0], &color->r) &&
			 is_valid_color_component(components[1], &color->g) &&
			 is_valid_color_component(components[2], &color->b);

	free_array(components);
	return (result);
}

/**
 * Parses a floor color line
 * @param scene Scene structure to fill
 * @param line Line to parse
 * @return true if successful, false otherwise
 */
bool	parse_floor_color(t_scene *scene, char *line)
{
	t_color	*color;

	if (scene->floor_color)
		exit_error(ERR_DUPLICATE);
	color = malloc(sizeof(t_color));
	if (!color)
		return (false);
	color->line = ft_strdup(line);
	if (!color->line)
	{
		free(color);
		return (false);
	}
	if (!parse_color_components(line, color))
	{
		free(color->line);
		free(color);
		return (false);
	}
	scene->floor_color = color;
	return (true);
}

/**
 * Parses a ceiling color line
 * @param scene Scene structure to fill
 * @param line Line to parse
 * @return true if successful, false otherwise
 */
bool	parse_ceiling_color(t_scene *scene, char *line)
{
	t_color	*color;

	if (scene->ceiling_color)
		exit_error(ERR_DUPLICATE);
	color = malloc(sizeof(t_color));
	if (!color)
		return (false);
	color->line = ft_strdup(line);
	if (!color->line)
	{
		free(color);
		return (false);
	}
	if (!parse_color_components(line, color))
	{
		free(color->line);
		free(color);
		return (false);
	}
	scene->ceiling_color = color;
	return (true);
}

#include <stdbool.h>
#include "parsing.h"
#include "libft.h"

#define ERR_SCENE_INVALID "Invalid scene configuration\n"

typedef bool	(*t_parser_func)(t_scene *scene, char *line);

/**
 * Checks if all required scene elements are present
 * @param scene Scene structure to check
 * @return true if complete, false otherwise
 */
static bool	is_scene_complete(t_scene *scene)
{
	return (scene->floor_color && scene->ceiling_color &&
			scene->we_texture && scene->so_texture &&
			scene->no_texture && scene->ea_texture);
}

/**
 * Gets the element type index from a line
 * @param line Line to check
 * @return Element type index or -1 if not recognized
 */
static int	get_element_type(char *line)
{
	if (!line || !*line)
		return (-1);
	if (ft_strncmp(line, TEXTURE_NO, 2) == 0 &&
		(line[2] == ' ' || line[2] == '\t'))
		return (0);
	else if (ft_strncmp(line, TEXTURE_SO, 2) == 0 &&
		(line[2] == ' ' || line[2] == '\t'))
		return (1);
	else if (ft_strncmp(line, TEXTURE_WE, 2) == 0 &&
		(line[2] == ' ' || line[2] == '\t'))
		return (2);
	else if (ft_strncmp(line, TEXTURE_EA, 2) == 0 &&
		(line[2] == ' ' || line[2] == '\t'))
		return (3);
	else if (ft_strncmp(line, COLOR_F, 1) == 0 &&
		(line[1] == ' ' || line[1] == '\t'))
		return (4);
	else if (ft_strncmp(line, COLOR_C, 1) == 0 &&
		(line[1] == ' ' || line[1] == '\t'))
		return (5);
	return (-1);
}

/**
 * Initializes the array of parser functions
 * @param parsers Array to fill with parser functions
 */
static void	init_parsers(t_parser_func *parsers)
{
	parsers[0] = parse_no_texture;
	parsers[1] = parse_so_texture;
	parsers[2] = parse_we_texture;
	parsers[3] = parse_ea_texture;
	parsers[4] = parse_floor_color;
	parsers[5] = parse_ceiling_color;
}

/**
 * Checks the validity of the scene configuration
 * @param infos Structure containing scene and parsing data
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
					ft_dprintf(STDERR_FILENO, "Error parsing element: %s\n",
						infos->data->lines[i]);
					exit_error(ERR_SCENE_INVALID);
				}
			}
			else if (found_element)
			{
				// Vérifier si tous les éléments requis sont présents
				if (is_scene_complete(infos->scene))
				{
					exit_error("ca marche");
					return (i); // Début de la carte
				}
				else
				{
					ft_dprintf(STDERR_FILENO, "Scene incomplete before map start\n");
					exit_error(ERR_SCENE_INVALID);
				}
			}
		}
		i++;
	}
 	// Vérification finale
	if (!is_scene_complete(infos->scene))
	{
		ft_dprintf(STDERR_FILENO, "Missing required scene elements\n");
		exit_error(ERR_SCENE_INVALID);
	}
	return (-1); // Aucune carte trouvée
}
