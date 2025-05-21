#include "structs.h"
#include "common.h"
#include "mlx.h"
#include "ray.h"
#include <math.h>

int	frame_display(t_main_struct *main_struct)
{
	int		row;
	double	teta;
	double	teta_cos_sin[2];

	row = 0;
	while (row < WINDOW_WIDTH)
	{
		teta = main_struct->player->fov_angle + main_struct->r_h_tab[row];
		teta_cos_sin[0] = cos(teta);
		teta_cos_sin[1] = sin(teta);
		if (teta < 0)
			teta += PIXX2;
		if (teta > PIXX2)
			teta -= PIXX2;
		render_one_ray(main_struct, teta_cos_sin, row, teta);
		row++;
	}
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr,
		main_struct->frame->sprite, 0, 0);
	return (0);
}
