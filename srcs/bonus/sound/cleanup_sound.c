/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_sound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:35 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:45:36 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound_internal.h"
#include "structs_b.h"

static void	cleanup_sounds(t_sound_mini *sound)
{
	if (sound->no_audio_device)
		return ;
	ma_sound_uninit(&sound->background_music);
	ma_sound_uninit(&sound->victory);
	ma_sound_uninit(&sound->death);
	ma_sound_uninit(&sound->door_sound);
	ma_sound_uninit(&sound->mj_sound);
	ma_sound_uninit(&sound->pickup_sound);
	ma_sound_uninit(&sound->fire_sound);
}

void	cleanup_sound(t_main_struct *main_struct)
{
	t_sound_mini	*sound;

	if (!main_struct->sound)
		return ;
	sound = (t_sound_mini *)main_struct->sound;
	cleanup_sounds(sound);
	ma_engine_uninit(&sound->engine);
	free(sound);
	main_struct->sound = NULL;
}
