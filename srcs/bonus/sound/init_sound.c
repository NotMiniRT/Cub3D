/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:37 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:45:38 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ft_dprintf.h"
#include "miniaudio_wrapper.h"
#include "sound_internal.h"
#include "sound.h"
#include "structs_b.h"

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
		ft_dprintf(STDERR_FILENO, RED ERROR_ENGINE_INIT RESET, result);
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
	ft_dprintf(STDERR_FILENO, RED ERROR_INITIALIZED RESET);
	return (init_engine_no_device(sound));
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
