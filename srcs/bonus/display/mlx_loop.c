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
	p->x = center_x + dx * 0.9995070605  - dy * 0.03139484039;
	p->y = center_y + dx * 0.03139484039 + dy * 0.9995070605 ;
}

void update_items(t_main_struct *main_struct)
{
	int	i;
	int x;
	int y;
	double mj_new_x;
	double mj_new_y;
	double norm;
	i = 0;
	if (main_struct->mj != NULL)
	{
		mj_new_x = (main_struct->mj->x - main_struct->player->x);
		mj_new_y = (main_struct->mj->y - main_struct->player->y);
		norm = sqrt(mj_new_x * mj_new_x + mj_new_y * mj_new_y);
		mj_new_x = mj_new_x / norm;
		mj_new_y = mj_new_y / norm;
		main_struct->mj->p1.x = main_struct->mj->x - 0.5 * mj_new_y;
		main_struct->mj->p1.y = main_struct->mj->y + 0.5 * mj_new_x;
		main_struct->mj->p2.x = main_struct->mj->x + 0.5 * mj_new_y;
		main_struct->mj->p2.y = main_struct->mj->y - 0.5 * mj_new_x;
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

static void put_victory_screen(t_main_struct *main_struct)
{
	t_image_cub *img;
	int 	i;
	int		j;


	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < (WINDOW_WIDTH * 4))
		{
			change_pixel_color(main_struct->frame, 0x000000, j, i);
			j = j + 4;
		}
		i++;
	}
	play_sound(main_struct, SOUND_VICTORY);
	get_image_cub_from_xpm_no_rot(main_struct, &img, \
			"assets/textures/mj/mjescape.xpm", 1080);
	if (img != NULL)
	{
		mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, main_struct->frame->sprite, 0, 0);
		mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, img->sprite, (WINDOW_WIDTH - 1080) * 0.5, 0);
		free_image_cub(main_struct, img);
	}
}

static void put_death_screen(t_main_struct *main_struct)
{
	t_image_cub *img;
	int 	i;
	int		j;


	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < (WINDOW_WIDTH * 4))
		{
			change_pixel_color(main_struct->frame, 0x000000, j, i);
			j = j + 4;
		}
		i++;
	}
	get_image_cub_from_xpm_no_rot(main_struct, &img, \
			"assets/textures/mj/mjcreepy.xpm", 1080);
	if (img != NULL)
	{
		mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, main_struct->frame->sprite, 0, 0);
		mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr, img->sprite, (WINDOW_WIDTH - 1080) * 0.5, 0);
		free_image_cub(main_struct, img);
	}
}

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
		if ((int)(main_struct->fuel * 100)%10 >= 8)
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

