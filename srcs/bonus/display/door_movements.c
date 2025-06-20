/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_movements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:55 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:56 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_int.h"
#include "structs_b.h"

void	up_doors(t_main_struct *main_struct, t_lst_int **lst)
{
	if (*lst == NULL)
		return ;
	(*(main_struct->doors))[(*lst)->index][2] = \
		(*(main_struct->doors))[(*lst)->index][2] + 1;
	if ((*(main_struct->doors))[(*lst)->index][2] >= 100)
	{
		remove_last_lst_int(lst);
		return ;
	}
	up_doors(main_struct, &((*lst)->next));
}

void	down_doors(t_main_struct *main_struct, t_lst_int **lst)
{
	if (*lst == NULL)
		return ;
	(*(main_struct->doors))[(*lst)->index][2] = \
		(*(main_struct->doors))[(*lst)->index][2] - 1;
	if ((*(main_struct->doors))[(*lst)->index][2] <= 0)
	{
		remove_last_lst_int(lst);
		return ;
	}
	down_doors(main_struct, &((*lst)->next));
}
