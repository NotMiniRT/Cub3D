/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:02 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:03 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;
typedef struct s_image_cub		t_image_cub;
typedef struct s_minimap		t_minimap;

# define MINIMAP_RADIUS 9
# define PLAYER_DOT_SIZE 6

bool	display_minimap(t_main_struct *main_struct);
bool	overlay(t_main_struct *main_struct);

void	draw_square_with_offset(t_image_cub *img, t_minimap *minimap);
void	draw_player(t_image_cub *img, double angle);
void	fill_minimap_background(t_image_cub *img);

#endif
