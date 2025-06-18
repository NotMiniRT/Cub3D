#include <X11/keysym.h>

#include "mlx.h"
#include "player.h"
#include "structs.h"

int	on_destroy(t_main_struct *main_struct)
{
	mlx_loop_end(main_struct->mlx_ptr);
	return (0);
}

int	release_move(int keysym, t_main_struct *main_struct)
{
	if (keysym == XK_a)
		main_struct->inputs[LEFT] = 0;
	else if (keysym == XK_d)
		main_struct->inputs[RIGHT] = 0;
	else if (keysym == XK_w)
		main_struct->inputs[UP] = 0;
	else if (keysym == XK_s)
		main_struct->inputs[DOWN] = 0;
	else if (keysym == XK_Right)
		main_struct->inputs[TRIGHT] = 0;
	else if (keysym == XK_Left)
		main_struct->inputs[TLEFT] = 0;
	else if (keysym == XK_Shift_L)
		main_struct->inputs[SHIFT] = 0;
	return (0);
}

void	toggle_move(t_main_struct *main_struct, int keysym)
{
	if (keysym == XK_a)
		main_struct->inputs[LEFT] = 1;
	else if (keysym == XK_d)
		main_struct->inputs[RIGHT] = 1;
	else if (keysym == XK_w)
		main_struct->inputs[UP] = 1;
	else if (keysym == XK_s)
		main_struct->inputs[DOWN] = 1;
	else if (keysym == XK_Right)
		main_struct->inputs[TRIGHT] = 1;
	else if (keysym == XK_Left)
		main_struct->inputs[TLEFT] = 1;
}

int	handle_input(int keysym, t_main_struct *main_struct)
{
	if (keysym == XK_Escape)
		on_destroy(main_struct);
	else if (keysym == XK_Shift_L)
		main_struct->inputs[SHIFT] = 1;
	else if (keysym == XK_a || keysym == XK_d
		|| keysym == XK_w || keysym == XK_s
		|| keysym == XK_Right || keysym == XK_Left)
		toggle_move(main_struct, keysym);
	return (0);
}
