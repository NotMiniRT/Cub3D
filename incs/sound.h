#ifndef SOUND_H
# define SOUND_H

typedef struct s_sound_mini		t_sound_mini;

# include <stdbool.h>

# include "structs_b.h"

# define SOUND_DOOR 1
# define SOUND_PICKUP 2
# define SOUND_MJ 3
# define SOUND_DEATH 4
# define SOUND_VICTORY 5

# define SOUND_FIRE 7

bool	init_sound(t_main_struct *main_struct);
void	play_sound(t_main_struct *main_struct, int sound_type);
void	cleanup_sound(t_main_struct *main_struct);

void	update_background_volume(t_main_struct *main_struct);

bool	load_sound_effects(t_sound_mini *sound);
bool	load_advanced_sounds(t_sound_mini *sound);
bool	load_basic_sounds(t_sound_mini *sound);
bool	load_background_music(t_sound_mini *sound);

#endif
