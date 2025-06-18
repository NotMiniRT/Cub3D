#include "common.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "miniaudio_wrapper.h"
#include "sound_internal.h"
#include "sound.h"
#include "stdbool.h"
#include "structs_b.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static bool	init_engine_normal(t_sound_mini *sound)
{
	if (ma_engine_init(NULL, &sound->engine) != MA_SUCCESS)
		return (false);
	sound->initialized = 1;
	sound->no_audio_device = 0;
	ft_dprintf(2, GREEN AUDIO_INITIALIZED RESET);
	return (true);
}

static bool	init_engine_no_device(t_sound_mini *sound)
{
	ma_engine_config	config;
	ma_result			result;

	config = ma_engine_config_init();
	config.noDevice = MA_TRUE;
	config.channels = 2;
	config.sampleRate = 48000;
	result = ma_engine_init(&config, &sound->engine);
	if (result != MA_SUCCESS)
	{
		ft_dprintf(2, RED ERROR_ENGINE_INIT RESET, result);
		return (false);
	}
	sound->initialized = 1;
	sound->no_audio_device = 1;
	ft_dprintf(2, GREEN AUDIO_INITIALIZED_NO_DEVICE RESET);
	return (true);
}

static bool	init_engine(t_sound_mini *sound)
{
	if (!check_bluetooth_audio_connected())
	{
		ft_dprintf(2, CYAN NO_BLUETOOTH RESET);
		return (init_engine_no_device(sound));
	}
	if (init_engine_normal(sound))
		return (true);
	ft_dprintf(2, RED ERROR_INITIALIZED RESET);
	return (init_engine_no_device(sound));
// 	if (ma_sound_init_from_file(&sound->engine,
// 			"assets/sound/glass.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
// 			NULL, NULL,
// 			&sound->pickup_sound) != MA_SUCCESS)
// 		return (false);
// 	if (ma_sound_init_from_file(&sound->engine,
// 			"assets/sound/door.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
// 			NULL, NULL,
// 			&sound->door_sound) != MA_SUCCESS)
// 		return (false);
// 	if (ma_sound_init_from_file(&sound->engine,
// 			"assets/sound/death.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
// 			NULL, NULL,
// 			&sound->death) != MA_SUCCESS)
// 		return (false);
// 	if (ma_sound_init_from_file(&sound->engine,
// 			"assets/sound/victory.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
// 			NULL, NULL,
// 			&sound->victory) != MA_SUCCESS)
// 		return (false);
// 	if (ma_sound_init_from_file(&sound->engine,
// 			"assets/sound/hehe.mp3",
// 			0, NULL, NULL,
// 		&sound->mj_sound) != MA_SUCCESS)
// 		return (false);
// 	if (ma_sound_init_from_file(&sound->engine,
// 			"assets/sound/fire.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
// 			NULL, NULL,
// 			&sound->fire_sound) != MA_SUCCESS)
// 		return (false);
// 	// set_sound(); ce qui est en dessous doit y aller
// 	ma_sound_set_attenuation_model(&sound->mj_sound, ma_attenuation_model_linear);
// 	ma_sound_set_min_distance(&sound->mj_sound, 0.8f);  // Very close for max volume
// 	ma_sound_set_max_distance(&sound->mj_sound, 15.0f);  // Much shorter distance to silence
// 	ma_sound_set_min_gain(&sound->mj_sound, 0.0f);      // Complete silence
// 	ma_sound_set_max_gain(&sound->mj_sound, 1.0f);      // Full volume
// 	ma_sound_set_rolloff(&sound->mj_sound, 2.0f);
// 	return (true);
}



bool	init_sound(t_main_struct *main_struct)
{
	t_sound_mini	*sound;

	sound = malloc(sizeof(t_sound_mini));
	if (!sound)
		return (false);
	sound->no_audio_device = 0;
	sound->initialized = 0;
	if (!init_engine(sound))
	{
		free(sound);
		return (false);
	}
	if (!load_background_music(sound) || !load_sound_effects(sound))
	{
		ma_engine_uninit(&sound->engine);
		free(sound);
		return (false);
	}
	main_struct->sound = sound;
	return (true);
}
