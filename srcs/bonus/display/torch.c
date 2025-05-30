#include <math.h>

#include "torch.h"
#include "common.h"
#include "libft.h"
#include "minimap.h"
#include "mlx.h"
#include "timer.h"
#include "image_b.h"

static inline void	change_pixel_color_opt(t_image_cub *img,
	int color, int x, int y)
{
	((int *)(img->buffer + (y * img->line_bytes) + (x)))[0] = color;
}

bool	init_torch(t_main_struct *main_struct)
{
	static char	*torch_paths[4] = {\
		TORCH_FRAME_1, TORCH_FRAME_2, \
		TORCH_FRAME_3, TORCH_FRAME_4};
	int			i;

	main_struct->torch = malloc(sizeof(t_torch));
	if (!main_struct->torch)
		return (false);
	ft_memset(main_struct->torch, 0, sizeof(t_torch));
	main_struct->torch->frame_duration = FRAME_DURATION;
	main_struct->torch->current_frame = 0;
	main_struct->torch->last_update = timestamp_in_ms(main_struct);
	i = 0;
	while (i < 4)
	{
		if (!get_image_cub_from_xpm_no_rot(main_struct,
				&(main_struct->torch->frames[i]), torch_paths[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	render_torch(t_main_struct *main_struct)
{
	size_t	current_time;

	if (!main_struct->torch)
		return (false);
	current_time = timestamp_in_ms(main_struct);
	if (current_time - main_struct->torch->last_update > \
			main_struct->torch->frame_duration)
	{
		main_struct->torch->current_frame = \
			(main_struct->torch->current_frame + 1) % 4;
		main_struct->torch->last_update = current_time;
	}
	return (true);
}

static void	draw_scaled_pixel(t_main_struct *main_struct, int color,
			int base_x, int base_y)
{
	static int	scale = 8;
	int			x;
	int			y;
	int			dest_x;
	int			dest_y;

	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			dest_x = (TORCH_X + x) * 4 + base_x * scale;
			dest_y = TORCH_Y + base_y * scale + y;
			if (dest_x >= 0 && dest_x < WINDOW_WIDTH * 4 && \
				dest_y >= 0 && dest_y < WINDOW_HEIGHT)
				change_pixel_color_opt(main_struct->frame, color, \
																dest_x, dest_y);
			x++;
		}
		y++;
	}
}

bool	display_torch(t_main_struct *main_struct)
{
	int			frame;
	int			i;
	int			j;
	int			color;

	if (!main_struct->torch)
		return (false);
	if (!render_torch(main_struct))
		return (false);
	frame = main_struct->torch->current_frame;
	i = 0;
	while (i < 256)
	{
		j = 0;
		while (j < 256)
		{
			color = get_color(main_struct->torch->frames[frame], j, i);
			if (color != 0)
				draw_scaled_pixel(main_struct, color, j, i);
			j++;
		}
		i++;
	}
	return (true);
}
