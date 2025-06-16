#include <stdlib.h>

#include "miniaudio_wrapper.h"
#include "structs_b.h"
#include "sound_internal.h"
#include "stdbool.h"

#include "ft_dprintf.h"

static bool	init_engine(t_sound_mini *sound)
{
	if (ma_engine_init(NULL, &sound->engine) != MA_SUCCESS)
		return (false);
	sound->initialized = 1;
	return (true);
}

static bool	load_background_music(t_sound_mini *sound)
{
	ma_result	result;

	result = ma_sound_init_from_file(&sound->engine,
			"assets/sound/background_stressing2.mp3",
			MA_SOUND_FLAG_STREAM, NULL, NULL,
			&sound->background_music);
	if (result != MA_SUCCESS)
	{
		ft_dprintf(2, "Failed to load background music: %d\n", result);
		return (false);
	}
	ma_sound_set_looping(&sound->background_music, MA_TRUE);
	result = ma_sound_start(&sound->background_music);
	if (result != MA_SUCCESS)
		ft_dprintf(2, "Failed to start background music: %d\n", result);
	else
		ft_dprintf(2, "Background music started successfully\n");
	return (true);
}

static bool	load_sound_effects(t_sound_mini *sound)
{
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/frog1.mp3",
			0, NULL, NULL,
			&sound->pickup_sound) != MA_SUCCESS)
		return (false);
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/door.mp3",
			0, NULL, NULL,
			&sound->door_sound) != MA_SUCCESS)
		return (false);
	if (ma_sound_init_from_file(&sound->engine,
			"assets/sound/hehe.mp3",
			0, NULL, NULL,
		&sound->mj_sound) != MA_SUCCESS)
		return (false);
	return (true);
}

bool	init_sound(t_main_struct *main_struct)
{
	t_sound_mini	*sound;

	sound = malloc(sizeof(t_sound_mini));
	if (!sound)
		return (false);
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
