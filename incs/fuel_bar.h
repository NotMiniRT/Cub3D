/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuel_bar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:27 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:28 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUEL_BAR_H
# define FUEL_BAR_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;
typedef struct s_image_cub		t_image_cub;

# define HUD_WIDTH 240
# define HUD_HEIGHT 450
# define HUD_X 80
# define HUD_Y 420
# define GAUGE_WIDTH 30
# define GAUGE_HEIGHT 370
# define GAUGE_X 15
# define GAUGE_Y 65
# define GAUGE_BORDER 2

bool	display_hud(t_main_struct *main_struct);

void	draw_fuel_gauge(t_image_cub *img, int fuel_level);
void	hud_set_pixel(t_image_cub *img, int x, int y, int color);

#endif
