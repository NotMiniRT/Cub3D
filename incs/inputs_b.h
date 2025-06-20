/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_b.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:34 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:35 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_B_H
# define INPUTS_B_H

typedef struct s_main_struct	t_main_struct;

int	on_destroy(t_main_struct *main_struct);
int	handle_input(int keysym, t_main_struct *main_struct);
int	release_move(int keysym, t_main_struct *main_struct);

int	handle_mouse_move(int x, int y, t_main_struct *main_struct);
int	handle_mouse_press(int button, int x, int y, t_main_struct *main_struct);
int	handle_mouse_rl(int button, int x, int y, t_main_struct *main_struct);

#endif
