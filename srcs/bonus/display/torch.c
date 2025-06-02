#include <math.h>

#include "torch.h"
#include "common.h"
#include "libft.h"
#include "minimap.h"
#include "mlx.h"
#include "timer.h"
#include "image_b.h"


bool	init_torch(t_main_struct *main_struct)
{
	static char	*torch_paths[TORCH_FRAME_COUNT] = {
		TORCH_FRAME_1, TORCH_FRAME_2,
		TORCH_FRAME_3, TORCH_FRAME_4
	};
	int			i = -1;

	main_struct->torch = malloc(sizeof(t_torch));
	if (!main_struct->torch)
		return (false);
	ft_memset(main_struct->torch, 0, sizeof(t_torch));
	main_struct->torch->frame_duration = TORCH_FRAME_DURATION;
	main_struct->torch->last_update = timestamp_in_ms(main_struct);
	while (++i < TORCH_FRAME_COUNT)
	{
		if (!get_image_cub_from_xpm_no_rot(main_struct,
				&(main_struct->torch->frames[i]), torch_paths[i]))
		{
			while (--i >= 0)
				free_image_cub(main_struct, main_struct->torch->frames[i]);
			free(main_struct->torch);
			main_struct->torch = NULL;
			return (false);
		}
	}
	return (true);
}

static bool	update_torch_animation(t_main_struct *main_struct)
{
	size_t	current_time;

	if (!main_struct->torch)
		return (false);
	current_time = timestamp_in_ms(main_struct);
	if (current_time - main_struct->torch->last_update >
			main_struct->torch->frame_duration)
	{
		main_struct->torch->current_frame =
			(main_struct->torch->current_frame + 1) % TORCH_FRAME_COUNT;
		main_struct->torch->last_update = current_time;
	}
	return (true);
}

static void	draw_torch_pixel(t_main_struct *main_struct, int color,
			int src_x, int src_y)
{
	int	scale_x;
	int	scale_y;
	int	dest_x;
	int	dest_y;

	if (color == 0)
		return ;
	scale_y = 0;
	while (scale_y < TORCH_DISPLAY_SCALE)
	{
		scale_x = 0;
		while (scale_x < TORCH_DISPLAY_SCALE)
		{
			dest_x = TORCH_DISPLAY_X + (src_x * TORCH_DISPLAY_SCALE) + scale_x;
			dest_y = TORCH_DISPLAY_Y + (src_y * TORCH_DISPLAY_SCALE) + scale_y;
			if (dest_x >= 0 && dest_x < WINDOW_WIDTH &&
				dest_y >= 0 && dest_y < WINDOW_HEIGHT)
				change_pixel_color(main_struct->frame, color, dest_x, dest_y);
			scale_x++;
		}
		scale_y++;
	}
}

bool	display_torch(t_main_struct *ms)
{
	t_image_cub	*current_frame_img;
	int			src_x;
	int			src_y;
	int			color;

	if (!ms->torch || !ms->torch->frames[0])
		return (false);
	if (!update_torch_animation(ms))
		return (false);
	current_frame_img = ms->torch->frames[ms->torch->current_frame];
	if (!current_frame_img)
		return (false);
	src_y = 0;
	while (src_y < current_frame_img->height)
	{
		src_x = 0;
		while (src_x < current_frame_img->width)
		{
			color = get_color(current_frame_img, src_x, src_y);
			draw_torch_pixel(ms, color, src_x, src_y);
			src_x++;
		}
		src_y++;
	}
	return (true);
}
