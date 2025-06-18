#include "structs_b.h"
#include <stdbool.h>
#include "libft.h"
#include "parsing.h"
#include <stdio.h>

void	free_map_item_i(t_main_struct *main_struct, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(main_struct->map_items[j]);
		j++;
	}
	free(main_struct->map_items);
	main_struct->map_items = NULL;
}

void	free_map_item_ij(t_main_struct *main_struct)
{
	int		k;
	size_t	line;
	size_t	n;

	k = 0;
	while (k < main_struct->count_lines)
	{
		n = 0;
		line = ft_strlen(main_struct->map[k]);
		while (n <= line)
		{
			free(main_struct->map_items[k][n].door);
			n++;
		}
		k++;
	}
	free_map_item_i(main_struct, k);
}

t_object_door	*create_object_map_door(int doors[4])
{
	t_object_door	*door;

	door = malloc(sizeof(t_object_door));
	if (door == NULL)
		return (NULL);
	door->x = doors[0];
	door->y = doors[1];
	door->status = doors[2];
	door->side = doors[3];
	if (door->side == VERTICAL)
	{
		door->p1.x = door->x + 0.5;
		door->p1.y = door->y;
		door->p2.x = door->x + 0.5;
		door->p2.y = door->y + 1;
	}
	else
	{
		door->p1.x = door->x;
		door->p1.y = door->y + 0.5;
		door->p2.x = door->x + 1;
		door->p2.y = door->y + 0.5;
	}
	return (door);
}

t_object_collectible	*create_object_map_item(int item[2])
{
	t_object_collectible	*new_item;

	new_item = malloc(sizeof(t_object_collectible));
	if (new_item == NULL)
		return (NULL);
	new_item->x = item[0];
	new_item->y = item[1];
	new_item->status = 1;
	new_item->p1.x = new_item->x + 0.5;
	new_item->p1.y = new_item->y;
	new_item->p2.x = new_item->x + 0.5;
	new_item->p2.y = new_item->y + 1;
	return (new_item);
}

bool	fill_map_object(t_main_struct *ms)
{
	int			i;
	t_objects	object;

	i = 0;
	while (i < 100 && (*ms->doors)[i][0] != 0)
	{
		object.door = create_object_map_door((*ms->doors)[i]);
		if (object.door == NULL)
			return (false);
		ms->map_items[(*ms->doors)[i][1]][(*ms->doors)[i][0]] = object;
		i++;
	}
	i = 0;
	while (i < 100 && (*ms->items)[i][0] != 0)
	{
		object.item = create_object_map_item((*ms->items)[i]);
		if (object.item == NULL)
			return (false);
		ms->map_items[(*ms->items)[i][1]][(*ms->items)[i][0]] = object;
		i++;
	}
	return (true);
}

bool	map_object_set(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	main_struct->count_lines = 0;
	main_struct->count_row = 0;
	if (!main_struct->map)
		return (false);
	while (main_struct->map[main_struct->count_lines] != NULL)
		main_struct->count_lines++;
	if (main_struct->count_lines == 0)
		return (false);
	while (main_struct->map[0][main_struct->count_row] != '\0')
		main_struct->count_row++;
	main_struct->map_items = ft_calloc(main_struct->count_lines, sizeof(t_objects *));
	if (main_struct->map_items == NULL)
		return (false);
	while (i < main_struct->count_lines)
	{
		main_struct->map_items[i] = ft_calloc(ft_strlen(main_struct->map[i]) + 1, sizeof(t_objects));
		if (main_struct->map_items[i] == NULL)
		{
			free_map_item_i(main_struct, i);
			return (false);
		}
		i++;
	}
	if (!fill_map_object(main_struct))
		return (false);
	return (true);
}
