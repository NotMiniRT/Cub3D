#include <X11/keysym.h>
#include "main_struct.h"
#include "mlx.h"

int	on_destroy(t_main_struct *main_struct)
{
	mlx_loop_end(main_struct->mlx_ptr);
	return (0);
}
int	handle_input(int keysym, t_main_struct *main_struct)
{
	if (keysym == XK_Escape)
		on_destroy(main_struct);
	return (0);
}
