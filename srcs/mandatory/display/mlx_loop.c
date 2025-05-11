#include "main_struct.h"
#include "display.h"
#include "timer.h"
#include "player.h"
#include "stdio.h"
#include "time.h"

void	do_one_move(t_main_struct *main_struct)
{
	if (main_struct->inputs[UP] + main_struct->inputs[DOWN] == 1
		|| main_struct->inputs[RIGHT] + main_struct->inputs[LEFT] == 1)
		move_player(main_struct,
			main_struct->inputs[UP] - main_struct->inputs[DOWN],
			main_struct->inputs[RIGHT] - main_struct->inputs[LEFT]);
	if (main_struct->inputs[TRIGHT] + main_struct->inputs[TLEFT] == 1)
		turn_player(main_struct->player,
			main_struct->inputs[TRIGHT] - main_struct->inputs[TLEFT]);
}

int	mlx_loop_action(t_main_struct *main_struct)
{
	if (frame_display(main_struct))
		return (1);
	if (timestamp_in_ms(main_struct) - main_struct->last_move > 20
		&& is_moving(main_struct))
	{
		main_struct->last_move = timestamp_in_ms(main_struct);
		do_one_move(main_struct);
	}
	return (0);
}

// static int frame_count = 0;
// static clock_t last_time = 0;

// if (last_time == 0)
//     last_time = clock();

// frame_count++;

// clock_t now = clock();
// double elapsed = (double)(now - last_time) / CLOCKS_PER_SEC;

// if (elapsed >= 1.0) {
//     printf("FPS : %d\n", frame_count);
//     frame_count = 0;
//     last_time = now;
// }
