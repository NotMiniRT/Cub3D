/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:43:20 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:43:21 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_b.h"

void	add_front_lst_int(t_lst_int **list, int i)
{
	t_lst_int	*new_node;

	new_node = malloc(sizeof(t_lst_int));
	if (new_node == NULL)
		return ;
	new_node->next = *list;
	*list = new_node;
	new_node->index = i;
}

void	remove_last_lst_int(t_lst_int **list)
{
	if (*list == NULL)
		return ;
	if ((*list)->next == NULL)
	{
		free(*list);
		*list = NULL;
		return ;
	}
	if ((*list)->next->next == NULL)
	{
		free((*list)->next);
		(*list)->next = NULL;
		return ;
	}
	remove_last_lst_int(&((*list)->next));
}

void	free_lst_int(t_lst_int *list)
{
	if (list == NULL)
		return ;
	if (list->next != NULL)
		free_lst_int(list->next);
	free(list);
}
