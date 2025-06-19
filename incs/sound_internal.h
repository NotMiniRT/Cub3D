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
