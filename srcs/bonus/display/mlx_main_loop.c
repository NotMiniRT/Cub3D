#include <math.h>
#include <stdio.h>
#include <time.h>

#include "common.h"
#include "display_b.h"
#include "doors_b.h"
#include "image_b.h"
#include "inputs_b.h"
#include "main_struct_b.h"
#include "mlx.h"
#include "monster.h"
#include "player_b.h"
#include "sound.h"
#include "structs_b.h"
#include "timer_b.h"
#include "torch.h"

int	mlx_loop_action(t_main_struct *main_struct)
{
	if (main_struct->died > 0)
	{
		if (main_struct->died == 1)
		{
			if (main_struct->collectible_count == 0)
				put_victory_screen(main_struct);
			else
				put_death_screen(main_struct);
			main_struct->died = 2;
			main_struct->created_at = timestamp_in_ms(main_struct);
		}
		if (timestamp_in_ms(main_struct) - main_struct->created_at > 3000)
			on_destroy(main_struct);
		return (0);
	}
	update_items(main_struct);
	if (frame_display(main_struct))
		return (1);
	if (main_struct->mj != NULL && timestamp_in_ms(main_struct) - main_struct->mj->move_time > 30)
		move_monster(main_struct);
	if (timestamp_in_ms(main_struct) - main_struct->torch->move > 200)
	{
		main_struct->torch->move = timestamp_in_ms(main_struct);
		main_struct->torch->torch_x = TORCH_X + main_struct->last_move % 16;
		main_struct->torch->torch_y = TORCH_Y + main_struct->last_move % 24;
	}
	if (timestamp_in_ms(main_struct) - main_struct->fuel_time > 1000 && main_struct->fuel > 0.06)
	{
		if ((int)(main_struct->fuel * 100) %10 >= 8)
		{
			play_sound(main_struct, SOUND_FIRE);
		}
		main_struct->fuel_time = timestamp_in_ms(main_struct);
		main_struct->fuel = main_struct->fuel - 0.02;
		if (main_struct->fuel < 0.06)
			main_struct->fuel = 0.05;
		update_background_volume(main_struct);
	}
	if (timestamp_in_ms(main_struct) - main_struct->last_move > 20
		&& is_moving(main_struct))
	{
		main_struct->last_move = timestamp_in_ms(main_struct);
		do_one_move(main_struct);
	}
	if (timestamp_in_ms(main_struct) - main_struct->door_action > 25
		&& (main_struct->down_door != NULL || main_struct->up_door != NULL))
	{
		main_struct->door_action = timestamp_in_ms(main_struct);
		if (main_struct->up_door != NULL)
			up_doors(main_struct, main_struct->up_door);
		if (main_struct->down_door != NULL)
			down_doors(main_struct, main_struct->down_door);
	}
	return (0);
}
