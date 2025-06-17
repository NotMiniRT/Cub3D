#include <stdlib.h>

#include "miniaudio.h"
#include "structs_b.h"
#include "sound_internal.h"

void	cleanup_sound(t_main_struct *main_struct)
{
	t_sound_mini	*sound;

	if (!main_struct->sound)
		return ;
	sound = (t_sound_mini *)main_struct->sound;
	ma_sound_uninit(&sound->background_music);
	ma_sound_uninit(&sound->victory);
	ma_sound_uninit(&sound->death);
	ma_sound_uninit(&sound->door_sound);
	ma_sound_uninit(&sound->mj_sound);
	ma_sound_uninit(&sound->pickup_sound);
	ma_sound_uninit(&sound->fire_sound);
	ma_engine_uninit(&sound->engine);
	free(sound);
	main_struct->sound = NULL;
}
