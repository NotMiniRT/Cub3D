/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_b.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:09 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:10 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_B_H
# define DISPLAY_B_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;
typedef struct s_infos			t_infos;

int		frame_display(t_main_struct *main_struct);
int		mlx_loop_action(t_main_struct *main_struct);

bool	start_display(t_main_struct *main_struct, t_infos *infos);
bool	init_all_sprites(t_main_struct *main_struct, t_infos *infos);

void	put_death_screen(t_main_struct *main_struct);
void	put_victory_screen(t_main_struct *main_struct);
void	do_one_move(t_main_struct *main_struct);
void	update_items(t_main_struct *ms);

#endif
