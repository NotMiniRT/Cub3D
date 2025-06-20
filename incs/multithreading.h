/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:11 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:12 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREADING_H
# define MULTITHREADING_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;

# define JOIN_ERROR "Error: Failed to join thread [%d] (error code: %d)\n"

# define NUM_THREADS 8

typedef struct s_thread_data
{
	int				thread_id;
	int				start_col;
	int				end_col;
	t_main_struct	*main_struct;
	pthread_t		thread;
}	t_thread_data;

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
void	cleanup_threads(t_thread_manager *thread_manager);
void	calculate_thread_ranges(t_thread_manager *manager);
void	*thread_render_routine(void *arg);

#endif
