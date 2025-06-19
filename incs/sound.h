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

# define SOUND_FIRE 6

# define A2DP		"a2dp"
# define BLUETOOTH	"bluetooth"
# define BLUEZ		"bluez"
# define BT			"bt"
# define HEADSET	"headset"

# define DEV_NULL	"/dev/null"
# define TRUNCATE	"w"

# define AUDIO_INITIALIZED "Audio initialized with device\n"
# define AUDIO_INITIALIZED_NO_DEVICE "Audio initialized without device\n"
# define DEVICE_CONNECTED "✓ Connected Bluetooth audio device detected\n"
# define ERROR_ENGINE_INIT "Error: engine init : %d\n"
# define ERROR_INITIALIZED "Normal init failed -> fallback without device\n"
# define INIT_SOUND_FALSE "Warning: Sound initialization failed\n"
# define INIT_SOUND_TRUE "Sound initialized successfully\n"
# define NO_BLUETOOTH "No Bluetooth audio -> mute\n"
# define NO_DEVICE_CONNECTED "✗ No Bluetooth audio device connected\n"
# define PACTL_BLUETOOTH_GREP "pactl list cards | grep -i bluetooth"
# define PACTL_BLUEZ_GREP "pactl list sinks short | grep 'bluez_sink.*a2dp'"


bool	init_sound(t_main_struct *main_struct);
void	play_sound(t_main_struct *main_struct, int sound_type);
void	cleanup_sound(t_main_struct *main_struct);

void	update_background_volume(t_main_struct *main_struct);

bool	load_sound_effects(t_sound_mini *sound);
bool	load_advanced_sounds(t_sound_mini *sound);
bool	load_basic_sounds(t_sound_mini *sound);
bool	load_background_music(t_sound_mini *sound);

bool	check_bluetooth_audio_connected(void);

void	setup_child_process(int pipefd[2]);
pid_t	create_child_process(int pipefd[2]);
bool	execute_pactl_command(const char *cmd);

#endif
