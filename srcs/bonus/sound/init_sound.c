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
static void	close_extra_fds(int keep_fd)
{
	int	max_fd;
	int	fd;

	max_fd = sysconf(_SC_OPEN_MAX);
	fd = 3;
	while (fd < max_fd)
	{
		if (fd != keep_fd)
			close(fd);
		fd++;
	}
}

static void	setup_child_process(int pipefd[2])
{
	FILE	*devnull;

	close_extra_fds(pipefd[1]);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		exit(1);
	}
	devnull = fopen("/dev/null", "w");
	if (devnull)
	{
		dup2(fileno(devnull), STDERR_FILENO);
		fclose(devnull);
	}
	close(pipefd[1]);
}

static void	str_to_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
}

static bool	check_bluetooth_keywords(char *buffer)
{
	str_to_lowercase(buffer);
	if (ft_strnstr(buffer, "bluetooth", ft_strlen("bluetooth")))
		return (true);
	if (ft_strnstr(buffer, "bluez", ft_strlen("bluez")))
		return (true);
	if (ft_strnstr(buffer, "bt", ft_strlen("bt")))
		return (true);
	if (ft_strnstr(buffer, "a2dp", ft_strlen("a2dp")))
		return (true);
	if (ft_strnstr(buffer, "headset", ft_strlen("headset")))
		return (true);
	return (false);
}

static bool	read_and_check_output(int fd)
{
	char	buffer[256];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (check_bluetooth_keywords(buffer))
			return (true);
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	}
	return (false);
}

static pid_t	create_child_process(int pipefd[2])
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (pid);
}

static bool	execute_pactl_command(const char *cmd)
{
	int		pipefd[2];
	pid_t	pid;
	bool	found;
	int		status;

	pid = create_child_process(pipefd);
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		setup_child_process(pipefd);
		execl("/bin/sh", "sh", "-c", cmd, NULL);
		exit(1);
	}
	close(pipefd[1]);
	found = read_and_check_output(pipefd[0]);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	return (found);
}

static bool	check_cards_for_bluetooth(void)
{
	int		pipefd[2];
	pid_t	pid;
	char	buffer[256];
	ssize_t	bytes_read;
	int		status;

	pid = create_child_process(pipefd);
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		setup_child_process(pipefd);
		execl("/bin/sh", "sh", "-c", "pactl list cards | grep -i bluetooth",
			NULL);
		exit(1);
	}
	close(pipefd[1]);
	bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		return (ft_strlen(buffer) > 0);
	}
	return (false);
}

static bool	check_bluetooth_audio_connected(void)
{
	bool	bluetooth_found;

	bluetooth_found = execute_pactl_command(
			"pactl list sinks short | grep 'bluez_sink.*a2dp'");
	if (!bluetooth_found)
		bluetooth_found = check_cards_for_bluetooth();
	if (bluetooth_found)
		ft_dprintf(2, "✓ Périphérique audio Bluetooth connecté détecté\n");
	else
		ft_dprintf(2, "✗ Aucun périphérique audio Bluetooth connecté\n");
	return (bluetooth_found);
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
	if (!check_bluetooth_audio_connected())
	{
		ft_dprintf(2, "Pas de Bluetooth audio -> désactivation du son\n");
		return (init_engine_no_device(sound));
	}
	ft_dprintf(2, "Bluetooth audio détecté -> initialisation du son\n");
	if (init_engine_normal(sound))
		return (true);
	ft_dprintf(2, "Échec init normale -> fallback sans périphérique\n");
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
