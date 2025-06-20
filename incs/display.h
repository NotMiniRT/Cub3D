/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:14 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:15 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;
typedef struct s_infos			t_infos;

int		frame_display(t_main_struct *main_struct);
int		mlx_loop_action(t_main_struct *main_struct);
bool	start_display(t_main_struct *main_struct, t_infos *infos);

#endif
