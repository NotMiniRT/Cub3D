/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:46:00 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:46:01 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "structs_b.h"

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
