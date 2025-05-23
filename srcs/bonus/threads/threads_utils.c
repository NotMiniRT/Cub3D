#include <math.h>
#include <unistd.h>

#include "ft_dprintf.h"
#include "multithreading.h"
#include "ray_b.h"

/* remplace ton ancienne frame_display */
static void	process_ray_range(t_thread_data *data)
{
	int		row;
	double	teta;
	double	teta_cos_sin[2];

	row = data->start_col;
	while (row < data->end_col)
	{
		teta = data->main_struct->player->fov_angle + \
				data->main_struct->r_h_tab[row];
		teta_cos_sin[0] = cos(teta);
		if (teta_cos_sin[0] == 0)
			teta_cos_sin[0] = 0.00001;
		teta_cos_sin[1] = sin(teta);
		if (teta_cos_sin[1] == 0)
			teta_cos_sin[1] = 0.00001;
		if (teta < 0)
			teta += PIXX2;
		if (teta > PIXX2)
			teta -= PIXX2;
		render_one_ray(data->main_struct, teta_cos_sin, row, teta);
		row++;
	}
}

void	*thread_render_routine(void *arg)
{
	t_thread_data	*data;
	bool			should_stop;

	data = (t_thread_data *)arg;
	while (1)
	{
		pthread_barrier_wait(&data->main_struct->thread_manager->frame);
		pthread_mutex_lock(&data->main_struct->thread_manager->exit_mutex);
		should_stop = data->main_struct->thread_manager->should_exit;
		pthread_mutex_unlock(&data->main_struct->thread_manager->exit_mutex);
		if (should_stop)
			break ;
		process_ray_range(data);
		pthread_barrier_wait(&data->main_struct->thread_manager->render);
	}
	return (NULL);
}

void	cleanup_threads(t_thread_manager *thread_manager)
{
	int	i;
	int	join_result;

	if (!thread_manager)
		return ;
	pthread_mutex_lock(&thread_manager->exit_mutex);
	thread_manager->should_exit = true;
	pthread_mutex_unlock(&thread_manager->exit_mutex);
	pthread_barrier_wait(&thread_manager->frame);
	i = 0;
	while (i < NUM_THREADS)
	{
		join_result = pthread_join(thread_manager->threads[i].thread, NULL);
		if (join_result != 0)
			ft_dprintf(STDERR_FILENO, JOIN_ERROR, \
							thread_manager->threads[i].thread_id, join_result);
		i++;
	}
	pthread_barrier_destroy(&thread_manager->render);
	pthread_barrier_destroy(&thread_manager->frame);
	pthread_mutex_destroy(&thread_manager->exit_mutex);
	free(thread_manager);
	thread_manager = NULL;
}
