#include <X11/keysym.h>
#include "main_struct.h"
#include "mlx.h"
#include "player.h"

int	on_destroy(t_main_struct *main_struct)
{
	mlx_loop_end(main_struct->mlx_ptr);
	return (0);
}
int	handle_input(int keysym, t_main_struct *main_struct)
{
	if (keysym == XK_Escape)
		on_destroy(main_struct);
	if (keysym == XK_i)
		player_log(main_struct);
	if (keysym == XK_a)
		move_left_right(main_struct->player, 1);
	if (keysym == XK_d)
		move_left_right(main_struct->player, -1);
	if (keysym == XK_w)
		move_foward_backward(main_struct->player, 1);
	if (keysym == XK_s)
		move_foward_backward(main_struct->player, -1);
	if (keysym == XK_Right)
		turn(main_struct->player, 1);
	if (keysym == XK_Left)
		turn(main_struct->player, -1);
	return (0);
}
