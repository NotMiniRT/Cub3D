/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:21 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:22 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_B_H
# define DOORS_B_H

typedef struct s_main_struct	t_main_struct;
typedef struct s_lst_int		t_lst_int;

int		get_status_door(int x, int y, t_main_struct *main_struct);

void	up_doors(t_main_struct *main_struct, t_lst_int **lst);
void	down_doors(t_main_struct *main_struct, t_lst_int **lst);
void	activate_door_monster(t_main_struct *main_struct, int new_x, int new_y);

#endif
