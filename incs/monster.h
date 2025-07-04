/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:09 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:10 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONSTER_H
# define MONSTER_H

# define MJ_NO_NB "assets/textures/mj/mj-"

# define MJ_ESCAPE "assets/textures/mj/mjescape.xpm"
# define MJ_CREEPY "assets/textures/mj/mjcreepy.xpm"

# define XPM_EXTENSION ".xpm"

typedef struct s_main_struct	t_main_struct;
typedef struct s_infos			t_infos;

void	move_monster(t_main_struct *main_struct);
void	get_monster_dir(t_main_struct *main_struct);
bool	set_mj(t_main_struct *main_struct, t_infos *infos);

#endif
