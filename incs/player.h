/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:19 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:20 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player			t_player;
typedef struct s_infos			t_infos;
typedef struct s_main_struct	t_main_struct;

int		is_facing_up(double ray_angle);
int		is_facing_down(double ray_angle);
int		is_facing_left(double ray_angle);
int		is_facing_right(double ray_angle);
int		init_player(t_player *player, t_infos *infos);
void	turn_player(t_player *player, int turn_dir);
void	move_player(t_main_struct *main_struct,
			int move_dir_front, int move_dir_side);

#endif
