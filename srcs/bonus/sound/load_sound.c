#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "structs_b.h"
#include "sound_internal.h"
#include "stdbool.h"
#include "ft_dprintf.h"
#include "libft.h"

bool	load_background_music(t_sound_mini *sound)
{
	ma_result	result;

	if (sound->no_audio_device)
		return (true);
	result = ma_sound_init_from_file(&sound->engine,
			"assets/sound/background_stressing.mp3",
			MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_SPATIALIZATION,
			NULL, NULL,
			&sound->background_music);
	if (result != MA_SUCCESS)
		return (false);
	ma_sound_set_looping(&sound->background_music, MA_TRUE);
	ma_sound_set_volume(&sound->background_music, 0.6f);
	result = ma_sound_start(&sound->background_music);
	if (result != MA_SUCCESS)
		ft_dprintf(2, "Failed to start background music: %d\n", result);
	return (true);
}

bool	load_basic_sounds(t_sound_mini *sound)
{
	if (sound->no_audio_device)
		return (true);
	// if (ma_sound_init_from_file(&sound->engine,
	// 		"assets/sound/glass.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
	// 		NULL, NULL,
	// 		&sound->pickup_sound) != MA_SUCCESS)
	// 	return (false);
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/door.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
			NULL, NULL,
			&sound->door_sound) != MA_SUCCESS)
		return (false);
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/death.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
			NULL, NULL,
			&sound->death) != MA_SUCCESS)
		return (false);
	// if (ma_sound_init_from_file(&sound->engine,
	// 		"assets/sound/fire.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
	// 		NULL, NULL,
	// 		&sound->fire_sound) != MA_SUCCESS)
	// 	return (false);
	return (true);
}

bool	load_advanced_sounds(t_sound_mini *sound)
{
	if (sound->no_audio_device)
		return (true);
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/victory.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
			NULL, NULL,
			&sound->victory) != MA_SUCCESS)
		return (false);
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/hehe.mp3",
			0, NULL, NULL,
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
