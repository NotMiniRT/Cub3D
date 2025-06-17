#include "miniaudio.h"
#include "structs_b.h"
#include "sound_internal.h"
#include "sound.h"

void	update_background_volume(t_main_struct *main_struct)
{
	t_sound_mini	*sound;
	float			fuel_ratio;
	float			volume;

	if (!main_struct->sound)
		return ;
	sound = (t_sound_mini *)main_struct->sound;
	fuel_ratio = main_struct->fuel;
	volume = 0.8f - (main_struct->fuel * 0.6f);
	if (volume < 0.2f)
		volume = 0.2f;
	if (volume > 0.8f)
		volume = 0.8f;
	ma_sound_set_volume(&sound->background_music, volume);
}

static void	play_door_sound(t_sound_mini *sound)
{
	ma_sound_seek_to_pcm_frame(&sound->door_sound, 0);
	ma_sound_start(&sound->door_sound);
}

static void	play_death_sound(t_sound_mini *sound)
{
	ma_sound_seek_to_pcm_frame(&sound->death, 0);
	ma_sound_start(&sound->death);
}

static void	play_victory_sound(t_sound_mini *sound)
{
	ma_sound_seek_to_pcm_frame(&sound->victory, 0);
	ma_sound_start(&sound->victory);
}

static void	play_pickup_sound(t_sound_mini *sound)
{
	ma_sound_seek_to_pcm_frame(&sound->pickup_sound, 0);
	ma_sound_start(&sound->pickup_sound);
}

static void	play_mj_sound_positioned(t_sound_mini *sound, t_main_struct *main_struct)
{
	ma_sound_set_position(&sound->mj_sound, main_struct->mj->x, main_struct->mj->y, 0.0f); // le dernier parametre c'est pour de la 3D (axe Z)
	ma_engine_listener_set_position(&sound->engine, 0, main_struct->player->x, main_struct->player->y, 0.0f);
	ma_sound_seek_to_pcm_frame(&sound->mj_sound, 0);
	ma_sound_start(&sound->mj_sound);
}

void	play_sound(t_main_struct *main_struct, int sound_type)
{
	t_sound_mini	*sound;

	if (!main_struct->sound)
		return ;
	sound = (t_sound_mini *)main_struct->sound;
	if (sound_type == SOUND_DOOR)
		play_door_sound(sound);
	else if (sound_type == SOUND_PICKUP)
		play_pickup_sound(sound);
	else if (sound_type == SOUND_MJ)
		play_mj_sound_positioned(sound, main_struct);
	else if (sound_type == SOUND_VICTORY)
		play_victory_sound(sound);
	else if (sound_type == SOUND_DEATH)
		play_death_sound(sound);
}
