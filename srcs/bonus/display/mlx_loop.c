#include "main_struct_b.h"
#include "display_b.h"
#include "timer.h"
#include "player_b.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
#include "doors_b.h"
#include "monster.h"
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

void rotate_point(t_main_struct *main_struct, int i, t_point *p)
{
	double dx;
	double dy;
	double center_x;
	double center_y;
	
	center_x = (*main_struct->items)[i][0] + 0.5;
	center_y = (*main_struct->items)[i][1] + 0.5;
	dx = p->x - center_x;
	dy = p->y - center_y;
	p->x = center_x + dx * cos(0.0314) - dy * sin(0.0314);
	p->y = center_y + dx * sin(0.0314) + dy * cos(0.0314);
}

void update_items(t_main_struct *main_struct)
{
	int	i;
	int x;
	int y;
	i = 0;
	if (main_struct->mj != NULL)
	{
		main_struct->mj->p1.x = main_struct->mj->x + 0.5 * main_struct->mj->dir.y;
		main_struct->mj->p1.y = main_struct->mj->y + 0.5 * main_struct->mj->dir.x;
		main_struct->mj->p2.x = main_struct->mj->x - 0.5 * main_struct->mj->dir.y;
		main_struct->mj->p2.y = main_struct->mj->y - 0.5 * main_struct->mj->dir.x;
	}
	while (i < 100 && (*main_struct->items)[i][0] != 0)
	{
		if ((*main_struct->items)[i][2] == 1)
		{
			x = (*main_struct->items)[i][0];
			y = (*main_struct->items)[i][1];
			rotate_point(main_struct, i, &(main_struct->map_items[y][x].item->p1));
			rotate_point(main_struct, i, &(main_struct->map_items[y][x].item->p2));
		}
		i++;
	}
}

int	mlx_loop_action(t_main_struct *main_struct)
{
	static int frame_count = 0;
	static clock_t last_time = 0;

	if (last_time == 0)
		last_time = clock();

	frame_count++;

	clock_t now = clock();
	double elapsed = (double)(now - last_time) / CLOCKS_PER_SEC;

	if (elapsed >= 1.0) {
		printf("FPS : %d\n", frame_count);
		frame_count = 0;
		last_time = now;
	}
	update_items(main_struct);
	if (frame_display(main_struct))
		return (1);
	if (main_struct->mj != NULL && timestamp_in_ms(main_struct) - main_struct->mj->dir_time > 500)
		get_monster_dir(main_struct);
	if (main_struct->mj != NULL && timestamp_in_ms(main_struct) - main_struct->mj->move_time > 20)
		move_monster(main_struct);
	if (timestamp_in_ms(main_struct) - main_struct->fuel_time > 700 && main_struct->fuel != 1)
	{
		main_struct->fuel_time = timestamp_in_ms(main_struct);
		main_struct->fuel--;
		if (main_struct->fuel == 0)
			main_struct->fuel = 1;
	}
	if (timestamp_in_ms(main_struct) - main_struct->last_move > 20
		&& is_moving(main_struct))
	{
		main_struct->last_move = timestamp_in_ms(main_struct);
		do_one_move(main_struct);
	}
	if (timestamp_in_ms(main_struct) - main_struct->door_action > 20
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


