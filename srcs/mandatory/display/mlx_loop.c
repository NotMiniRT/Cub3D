#include "main_struct.h"
#include "display.h"
#include "timer.h"
#include "player.h"
#include "stdio.h"

void do_one_move(t_main_struct *main_struct)
{
	if (main_struct->inputs[UP] + main_struct->inputs[DOWN] == 1 || main_struct->inputs[RIGHT] + main_struct->inputs[LEFT] == 1)
		move_player(main_struct, main_struct->inputs[UP] - main_struct->inputs[DOWN], main_struct->inputs[RIGHT] - main_struct->inputs[LEFT]);
	if (main_struct->inputs[TRIGHT] + main_struct->inputs[TLEFT] == 1)
		turn_player(main_struct->player, main_struct->inputs[TRIGHT] - main_struct->inputs[TLEFT]);
}

int	mlx_loop_action(t_main_struct *main_struct)
{
	if (frame_display(main_struct))
		return (1);
	if (timestamp_in_ms(main_struct) - main_struct->last_move > 20 && is_moving(main_struct))
	{
		main_struct->last_move = timestamp_in_ms(main_struct);
		do_one_move(main_struct);
	}
	return (0);
}