/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:39 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:40 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_INT_H
# define LST_INT_H

typedef struct s_lst_int		t_lst_int;

void	add_front_lst_int(t_lst_int **list, int i);
void	remove_last_lst_int(t_lst_int **list);
void	free_lst_int(t_lst_int *list);

#endif
