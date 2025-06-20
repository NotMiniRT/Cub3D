/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:37 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:38 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

typedef struct s_main_struct	t_main_struct;

int	on_destroy(t_main_struct *main_struct);
int	handle_input(int keysym, t_main_struct *main_struct);
int	release_move(int keysym, t_main_struct *main_struct);

#endif
