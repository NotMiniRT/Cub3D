/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:40 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:45:41 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>

#include "common.h"
#include "ft_dprintf.h"
#include "sound_internal.h"
#include "sound.h"

static bool	check_audio_file_access(const char *path)
{
	if (access(path, F_OK | R_OK) == 0)
		return (true);
	ft_dprintf(STDERR_FILENO, YELLOW ERROR_AUDIO_ACCESS, path, RESET);
	return (false);
}

bool	load_background_music(t_sound_mini *sound)
{
	ma_result	result;

	if (sound->no_audio_device)
		return (true);
	if (!check_audio_file_access(BACKGROUND_PATH_SOUND))
		return (false);
	result = ma_sound_init_from_file(&sound->engine, BACKGROUND_PATH_SOUND,
			MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_SPATIALIZATION,
			NULL, NULL,
			&sound->background_music);
	if (result != MA_SUCCESS)
		return (false);
	ma_sound_set_looping(&sound->background_music, MA_TRUE);
	ma_sound_set_volume(&sound->background_music, 0.6f);
	result = ma_sound_start(&sound->background_music);
	if (result != MA_SUCCESS)
		ft_dprintf(STDERR_FILENO, ERROR_BG_START, result);
	return (true);
}

bool	load_basic_sounds(t_sound_mini *sound)
{
	if (sound->no_audio_device)
		return (true);
	if (!check_audio_file_access(GLASS_PATH_SOUND) || \
		ma_sound_init_from_file(&sound->engine, GLASS_PATH_SOUND, \
			MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, NULL,
			&sound->pickup_sound) != MA_SUCCESS)
		return (false);
	if (!check_audio_file_access(DOOR_PATH_SOUND) || \
		ma_sound_init_from_file(&sound->engine, DOOR_PATH_SOUND, \
			MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, NULL,
			&sound->door_sound) != MA_SUCCESS)
		return (false);
	if (!check_audio_file_access(DEATH_PATH_SOUND) || \
		ma_sound_init_from_file(&sound->engine, DEATH_PATH_SOUND, \
			MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, NULL,
			&sound->death) != MA_SUCCESS)
		return (false);
	if (!check_audio_file_access(FIRE_PATH_SOUND) || \
		ma_sound_init_from_file(&sound->engine, FIRE_PATH_SOUND, \
			MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, NULL,
			&sound->fire_sound) != MA_SUCCESS)
		return (false);
	return (true);
}

bool	load_advanced_sounds(t_sound_mini *sound)
{
	if (sound->no_audio_device)
		return (true);
	if (!check_audio_file_access(VICTORY_PATH_SOUND) || \
		ma_sound_init_from_file(&sound->engine, VICTORY_PATH_SOUND, \
			MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, NULL,
			&sound->victory) != MA_SUCCESS)
		return (false);
	if (!check_audio_file_access(HEHE_PATH_SOUND) || \
		ma_sound_init_from_file(&sound->engine, HEHE_PATH_SOUND,
			MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, NULL,
			&sound->mj_sound) != MA_SUCCESS)
		return (false);
	ma_sound_set_attenuation_model(&sound->mj_sound,
		ma_attenuation_model_linear);
	ma_sound_set_min_distance(&sound->mj_sound, 0.8f);
	ma_sound_set_max_distance(&sound->mj_sound, 15.0f);
	ma_sound_set_min_gain(&sound->mj_sound, 0.0f);
	ma_sound_set_max_gain(&sound->mj_sound, 1.0f);
	ma_sound_set_rolloff(&sound->mj_sound, 2.0f);
	return (true);
}

bool	load_sound_effects(t_sound_mini *sound)
{
	if (!load_basic_sounds(sound))
		return (false);
	if (!load_advanced_sounds(sound))
		return (false);
	return (true);
}
