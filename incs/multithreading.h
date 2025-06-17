#ifndef MULTITHREADING_H
# define MULTITHREADING_H

# include <pthread.h>
# include <stdbool.h>

# include "common.h"
# include "structs_b.h"

# define JOIN_ERROR "Error: Failed to join thread [%d] (error code: %d)\n"

# define NUM_THREADS 8

/* Structure de données pour chaque thread */
typedef struct s_thread_data
{
	int				thread_id;
	int				start_col;
	int				end_col;
	t_main_struct	*main_struct;
	pthread_t		thread;
}	t_thread_data;

/* Structure globale de gestion des threads */
typedef struct s_thread_manager
{
	t_thread_data		threads[NUM_THREADS];
	pthread_barrier_t	render;
	pthread_barrier_t	frame;
	pthread_mutex_t		exit_mutex;
	bool				should_exit;
}	t_thread_manager;

/* Fonctions de gestion des threads */
bool	init_threads(t_main_struct *main_struct);
void    cleanup_threads(t_thread_manager *thread_manager);
void	calculate_thread_ranges(t_thread_manager *manager);
void	*thread_render_routine(void *arg);

#endif
