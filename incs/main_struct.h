/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:45 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:46 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

typedef struct s_main_struct	t_main_struct;

int		is_moving(t_main_struct *t_main_struct);
void	free_main_struct(t_main_struct *main_struct);
int		init_r_h_tab(t_main_struct *main_struct);

#endif
