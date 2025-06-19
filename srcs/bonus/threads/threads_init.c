#include "common.h"
#include "multithreading.h"
#include "structs_b.h"

void	calculate_thread_ranges(t_thread_manager *manager)
{
	int	columns_per_thread;
	int	extra_columns;
	int	current_col;
	int	i;

	columns_per_thread = WINDOW_WIDTH / NUM_THREADS;
	extra_columns = WINDOW_WIDTH % NUM_THREADS;
	current_col = 0;
	i = 0;
	while (i < NUM_THREADS)
	{
		manager->threads[i].start_col = current_col;
		current_col += columns_per_thread;
		if (extra_columns > 0)
		{
			current_col++;
			extra_columns--;
		}
		manager->threads[i].end_col = current_col;
		i++;
	}
}

static bool	init_thread_barriers(t_thread_manager *manager)
{
	if (pthread_mutex_init(&manager->exit_mutex, NULL) != 0)
		return (false);
	if (pthread_barrier_init(&manager->render, NULL, NUM_THREADS + 1) != 0)
	{
		pthread_mutex_destroy(&manager->exit_mutex);
		return (false);
	}
	if (pthread_barrier_init(&manager->frame, NULL, NUM_THREADS + 1) != 0)
	{
		pthread_mutex_destroy(&manager->exit_mutex);
		pthread_barrier_destroy(&manager->render);
		return (false);
	}
	return (true);
}

static bool	init_one_thread(t_thread_manager *manager, int i)
{
	manager->threads[i].thread_id = i;
	if (pthread_create(&manager->threads[i].thread, NULL,
			thread_render_routine, &manager->threads[i]) != 0)
		return (false);
	return (true);
}

static bool	create_all_threads(t_thread_manager *manager)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		if (!init_one_thread(manager, i))
			return (false);
		i++;
	}
	return (true);
}

bool	init_threads(t_main_struct *main_struct)
{
	static int	i = -1;

	main_struct->thread_manager = malloc(sizeof(t_thread_manager));
	if (!main_struct->thread_manager)
		return (false);
	main_struct->thread_manager->should_exit = false;
	if (!init_thread_barriers(main_struct->thread_manager))
	{
		free(main_struct->thread_manager);
		return (false);
	}
	calculate_thread_ranges(main_struct->thread_manager);
	while (++i < NUM_THREADS)
		main_struct->thread_manager->threads[i].main_struct = main_struct;
	if (!create_all_threads(main_struct->thread_manager))
	{
		pthread_mutex_lock(&main_struct->thread_manager->exit_mutex);
		main_struct->thread_manager->should_exit = true;
		pthread_mutex_unlock(&main_struct->thread_manager->exit_mutex);
		cleanup_threads(main_struct->thread_manager);
		return (false);
	}
	return (true);
}
