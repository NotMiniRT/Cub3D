#include "libft.h"
#include "parsing.h"
#include "structs_b.h"

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

static bool	map_object_alloc(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->count_lines)
	{
		main_struct->map_items[i] = \
			ft_calloc(ft_strlen(main_struct->map[i]) + 1, sizeof(t_objects));
		if (main_struct->map_items[i] == NULL)
		{
			free_map_item_i(main_struct, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	map_object_set(t_main_struct *main_struct)
{
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
	main_struct->map_items = \
		ft_calloc(main_struct->count_lines, sizeof(t_objects *));
	if (main_struct->map_items == NULL)
		return (false);
	if (!map_object_alloc(main_struct))
		return (false);
	if (!fill_map_object(main_struct))
		return (false);
	return (true);
}
