#include "ft_dprintf.h"
#include "sound_internal.h"
#include "sound.h"
#include "structs_b.h"

void	update_background_volume(t_main_struct *main_struct)
{
	t_sound_mini	*sound;
	float			fuel_ratio;
	float			volume;

	if (!main_struct->sound)
		return ;
	sound = (t_sound_mini *)main_struct->sound;
	if (sound->no_audio_device)
		return ;
	fuel_ratio = main_struct->fuel;
	volume = 0.8f - (main_struct->fuel * 0.6f);
	if (volume < 0.2f)
		volume = 0.2f;
	if (volume > 0.8f)
		volume = 0.8f;
	ma_sound_set_volume(&sound->background_music, volume);
}

static void	play_generic_sound(t_sound_mini *sound, \
									ma_sound *sound_obj, const char *sound_name)
{
	ma_result	result;

	if (sound->no_audio_device)
		return ;
	result = ma_sound_seek_to_pcm_frame(sound_obj, 0);
	if (result != MA_SUCCESS)
	{
		ft_dprintf(2, "Failed to seek %s sound: %d\n", sound_name, result);
		return ;
	}
	result = ma_sound_start(sound_obj);
	if (result != MA_SUCCESS)
		ft_dprintf(2, "Failed to start %s sound: %d\n", sound_name, result);
}

static void	play_mj_sound_positioned(t_sound_mini *sound, t_main_struct *ms)
{
	ma_result	result;

	if (sound->no_audio_device)
		return ;
	ma_sound_set_position(&sound->mj_sound, ms->mj->x,
		ms->mj->y, 0.0f);
	ma_engine_listener_set_position(&sound->engine, 0, ms->player->x,
		ms->player->y, 0.0f);
	result = ma_sound_seek_to_pcm_frame(&sound->mj_sound, 0);
	if (result != MA_SUCCESS)
	{
		ft_dprintf(2, "Failed to seek MJ sound: %d\n", result);
		return ;
	}
	result = ma_sound_start(&sound->mj_sound);
	if (result != MA_SUCCESS)
		ft_dprintf(2, "Failed to start MJ sound: %d\n", result);
}

void	play_sound(t_main_struct *main_struct, int sound_type)
{
	t_sound_mini	*sound;

	if (!main_struct->sound)
		return ;
	sound = (t_sound_mini *)main_struct->sound;
	if (sound_type == SOUND_DOOR)
		play_generic_sound(sound, &sound->door_sound, "door");
	else if (sound_type == SOUND_PICKUP)
		play_generic_sound(sound, &sound->pickup_sound, "pickup");
	else if (sound_type == SOUND_MJ)
		play_mj_sound_positioned(sound, main_struct);
	else if (sound_type == SOUND_VICTORY)
		play_generic_sound(sound, &sound->victory, "victory");
	else if (sound_type == SOUND_DEATH)
		play_generic_sound(sound, &sound->death, "death");
	else if (sound_type == SOUND_FIRE)
		play_generic_sound(sound, &sound->fire_sound, "fire");
}
