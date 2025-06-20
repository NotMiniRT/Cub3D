/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_b.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:16 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:17 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_B_H
# define PLAYER_B_H

typedef struct s_main_struct	t_main_struct;
typedef struct s_infos			t_infos;
typedef struct s_player			t_player;

int		is_facing_up(double ray_angle);
int		is_facing_down(double ray_angle);
int		is_facing_left(double ray_angle);
int		is_facing_right(double ray_angle);
int		init_player(t_player *player, t_infos *infos);
void	turn_player(t_player *player, int turn_dir);
void	move_player(t_main_struct *main_struct,
			int move_dir_front, int move_dir_side);
void	open_door(t_main_struct *main_struct);
void	rotate_player_by_mouse(t_player *player, double rotation);

void	one_direction(t_main_struct *ms, double move_x, double move_y);

#endif
