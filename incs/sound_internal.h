/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:28 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:29 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_INTERNAL_H
# define SOUND_INTERNAL_H

# include "miniaudio.h"

typedef struct s_sound_mini
{
	ma_engine	engine;
	ma_sound	background_music;
	ma_sound	victory;
	ma_sound	death;
	ma_sound	door_sound;
	ma_sound	mj_sound;
	ma_sound	pickup_sound;
	ma_sound	fire_sound;
	int			initialized;
	int			no_audio_device;
}	t_sound_mini;

#endif
