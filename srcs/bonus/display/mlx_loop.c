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

void	rotate_point(t_main_struct *main_struct, int i, t_point *p)
{
	double	dx;
	double	dy;
	double	center_x;
	double	center_y;

	center_x = (*main_struct->items)[i][0] + 0.5;
	center_y = (*main_struct->items)[i][1] + 0.5;
	dx = p->x - center_x;
	dy = p->y - center_y;
	p->x = center_x + dx * 0.9995070605 - dy * 0.03139484039;
	p->y = center_y + dx * 0.03139484039 + dy * 0.9995070605 ;
}

void	update_items(t_main_struct *ms)
{
	t_update_item	d;

	d.i = -1;
	if (ms->mj != NULL)
	{
		d.mj_new_x = (ms->mj->x - ms->player->x);
		d.mj_new_y = (ms->mj->y - ms->player->y);
		d.norm = sqrt(d.mj_new_x * d.mj_new_x + d.mj_new_y * d.mj_new_y);
		d.mj_new_x = d.mj_new_x / d.norm;
		d.mj_new_y = d.mj_new_y / d.norm;
		ms->mj->p1.x = ms->mj->x - 0.5 * d.mj_new_y;
		ms->mj->p1.y = ms->mj->y + 0.5 * d.mj_new_x;
		ms->mj->p2.x = ms->mj->x + 0.5 * d.mj_new_y;
		ms->mj->p2.y = ms->mj->y - 0.5 * d.mj_new_x;
	}
	while (++d.i < 100 && (*ms->items)[d.i][0] != 0)
	{
		if ((*ms->items)[d.i][2] == 1)
		{
			d.x = (*ms->items)[d.i][0];
			d.y = (*ms->items)[d.i][1];
			rotate_point(ms, d.i, &(ms->map_items[d.y][d.x].item->p1));
			rotate_point(ms, d.i, &(ms->map_items[d.y][d.x].item->p2));
		}
	}
}

void	put_victory_screen(t_main_struct *main_struct)
{
	t_image_cub	*img;
	int			i;
	int			j;

	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < (WINDOW_WIDTH * 4))
		{
			change_pixel_color(main_struct->frame, 0x000000, j, i);
			j = j + 4;
		}
	}
	play_sound(main_struct, SOUND_VICTORY);
	get_image_cub_from_xpm_no_rot(main_struct, &img, \
			"assets/textures/mj/mjescape.xpm", 1080);
	if (img != NULL)
	{
		mlx_put_image_to_window(main_struct->mlx_ptr, \
			main_struct->win_ptr, main_struct->frame->sprite, 0, 0);
		mlx_put_image_to_window(main_struct->mlx_ptr, \
			main_struct->win_ptr, img->sprite, (WINDOW_WIDTH - 1080) * 0.5, 0);
		free_image_cub(main_struct, img);
	}
}

void	put_death_screen(t_main_struct *main_struct)
{
	t_image_cub	*img;
	int			i;
	int			j;

	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < (WINDOW_WIDTH * 4))
		{
			change_pixel_color(main_struct->frame, 0x000000, j, i);
			j = j + 4;
		}
	}
	get_image_cub_from_xpm_no_rot(main_struct, &img, \
			"assets/textures/mj/mjcreepy.xpm", 1080);
	if (img != NULL)
	{
		mlx_put_image_to_window(main_struct->mlx_ptr, \
			main_struct->win_ptr, main_struct->frame->sprite, 0, 0);
		mlx_put_image_to_window(main_struct->mlx_ptr, \
			main_struct->win_ptr, img->sprite, (WINDOW_WIDTH - 1080) * 0.5, 0);
		free_image_cub(main_struct, img);
	}
}
