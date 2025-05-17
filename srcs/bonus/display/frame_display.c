#include "structs.h"
#include "common.h"
#include "mlx.h"
#include "ray.h"
#include <math.h>
#include "image.h"
#include "minimap.h"
#include "multithreading.h"

/**
 * Appeler les thread ici apres mlx_put_image (en gros)
 * Avec 3 etats :
 * 0 initialisation
 * 1 calcul
 * 2 attente tous les threads calculs finis
 * boucle
 * main process = update image + status
 */
// int	frame_display(t_main_struct *main_struct)
// {
// 	int		row;
// 	double	teta;
// 	double	teta_cos_sin[2];

// 	row = 0;
// 	while (row < WINDOW_WIDTH)
// 	{
// 		teta = main_struct->player->fov_angle + main_struct->r_h_tab[row];
// 		teta_cos_sin[0] = cos(teta);
// 		teta_cos_sin[1] = sin(teta);
// 		if (teta < 0)
// 			teta += PIX2;
// 		if (teta > PIX2)
// 			teta -= PIX2;
// 		render_one_ray(main_struct, teta_cos_sin, row, teta);
// 		row++;
// 	}
// 	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr,
// 		main_struct->frame->sprite, 0, 0);
// 	if (!overlay(main_struct))
// 		return (1);
// 	return (0);
// }

static void	wait_for_threads_rendering(t_main_struct *main_struct)
{
	pthread_barrier_wait(&main_struct->thread_manager->render);
}

static void	start_next_frame(t_main_struct *main_struct)
{
	pthread_barrier_wait(&main_struct->thread_manager->frame);
}

int	frame_display(t_main_struct *main_struct)
{
	start_next_frame(main_struct);
	wait_for_threads_rendering(main_struct);
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr,
		main_struct->frame->sprite, 0, 0);
	if (!overlay(main_struct))
		return (1);
	return (0);
}
