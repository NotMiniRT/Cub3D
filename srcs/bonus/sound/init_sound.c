#include <stdlib.h>
#include "miniaudio_wrapper.h"
#include "structs_b.h"
#include "sound_internal.h"
#include "stdbool.h"
#include "ft_dprintf.h"

static bool	check_audio_devices(void)
{
	ma_context		context;
	ma_device_info	*playback_infos;
	ma_uint32		playback_count;
	ma_device_info	*capture_infos;
	ma_uint32		capture_count;
	ma_result		result;

	result = ma_context_init(NULL, 0, NULL, &context);
	if (result != MA_SUCCESS)
		return (false);
	result = ma_context_get_devices(&context, &playback_infos, &playback_count,
			&capture_infos, &capture_count);
	ma_context_uninit(&context);
	if (result != MA_SUCCESS)
		return (false);
	return (playback_count > 0);
}

static bool	init_engine_normal(t_sound_mini *sound)
{
	if (ma_engine_init(NULL, &sound->engine) != MA_SUCCESS)
		return (false);
	sound->initialized = 1;
	sound->no_audio_device = 0;
	ft_dprintf(2, "Audio initialisé avec périphérique\n");
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
		ft_dprintf(2, "Erreur init engine audio : %d\n", result);
		return (false);
	}
	sound->initialized = 1;
	sound->no_audio_device = 1;
	ft_dprintf(2, "Audio initialisé sans périphérique\n");
	return (true);
}

static bool	init_engine(t_sound_mini *sound)
{
	if (check_audio_devices())
	{
		if (init_engine_normal(sound))
			return (true);
	}
	ft_dprintf(2, "Tentative init sans périphérique audio...\n");
	return (init_engine_no_device(sound));
}

static bool	load_background_music(t_sound_mini *sound)
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
	{
		ft_dprintf(2, "Failed to load background music: %d\n", result);
		return (false);
	}
	ma_sound_set_looping(&sound->background_music, MA_TRUE);
	ma_sound_set_volume(&sound->background_music, 0.6f);
	result = ma_sound_start(&sound->background_music);
	if (result != MA_SUCCESS)
		ft_dprintf(2, "Failed to start background music: %d\n", result);
	else
		ft_dprintf(2, "Background music started successfully\n");
	return (true);
}

static bool	load_basic_sounds(t_sound_mini *sound)
{
	if (sound->no_audio_device)
		return (true);
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/frog1.mp3", MA_SOUND_FLAG_NO_SPATIALIZATION,
			NULL, NULL,
			&sound->pickup_sound) != MA_SUCCESS)
		return (false);
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
	return (true);
}

static bool	load_advanced_sounds(t_sound_mini *sound)
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

static bool	load_sound_effects(t_sound_mini *sound)
{
	if (!load_basic_sounds(sound))
		return (false);
	if (!load_advanced_sounds(sound))
		return (false);
	return (true);
}

bool	init_sound(t_main_struct *main_struct)
{
	t_sound_mini	*sound;

	sound = malloc(sizeof(t_sound_mini));
	if (!sound)
		return (false);
	sound->no_audio_device = 0;
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
