#include "mlx.h"
#include "player_b.h"
#include "common.h"

int	on_destroy(t_main_struct *main_struct)
{
	if (main_struct->mouse_left_pressed)
		mlx_mouse_show(main_struct->mlx_ptr, main_struct->win_ptr);
	mlx_loop_end(main_struct->mlx_ptr);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_main_struct *main_struct)
{
	if (button == 1)
	{
		main_struct->mouse_left_pressed = 1;
		main_struct->lock_mouse_x = x;
		main_struct->lock_mouse_y = y;
		mlx_mouse_hide(main_struct->mlx_ptr, main_struct->win_ptr);
	}
	return (0);
}

int	handle_mouse_rl(int button, int x, int y, t_main_struct *main_struct)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		main_struct->mouse_left_pressed = 0;
		main_struct->is_mouse_locked = 0;
		mlx_mouse_show(main_struct->mlx_ptr, main_struct->win_ptr);
	}
	return (0);
}

int	handle_mouse_move(int x, int y, t_main_struct *main_struct)
{
	int		delta_x;
	double	rotation;

	(void)y;
	if (main_struct->mouse_left_pressed && !main_struct->is_mouse_locked)
	{
		delta_x = x - main_struct->lock_mouse_x;
		if (delta_x != 0)
		{
			rotation = delta_x * MOUSE_SENSITIVITY;
			rotate_player_by_mouse(main_struct->player, rotation);
			main_struct->is_mouse_locked = 1;
			mlx_mouse_move(main_struct->mlx_ptr, main_struct->win_ptr,
				main_struct->lock_mouse_x,
				main_struct->lock_mouse_y);
		}
	}
	else
		main_struct->is_mouse_locked = 0;
	return (0);
}
