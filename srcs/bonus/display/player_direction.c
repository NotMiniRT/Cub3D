#include <math.h>

#include "common.h"
#include "doors_b.h"
#include "parsing.h"
#include "sound.h"
#include "structs_b.h"
#include "player_b.h"

static int	is_position_accessible(t_main_struct *ms, int x, int y)
{
	if (ms->map[y][x] == '1')
		return (0);
	if (ms->map[y][x] == 'D' && get_status_door(y, x, ms) != 0)
		return (0);
	return (1);
}

static void	adjust_horizontal_position(t_main_struct *ms, double move_x)
{
	if (ms->player->x - move_x < 0)
		ms->player->x = floor(move_x) - 0.01;
	else if (ms->player->x - move_x > 0)
		ms->player->x = ceil(move_x) + 0.01;
}

static void	adjust_vertical_position(t_main_struct *ms, double move_y)
{
	if (ms->player->y - move_y < 0)
		ms->player->y = floor(move_y) - 0.01;
	else if (ms->player->y - move_y > 0)
		ms->player->y = ceil(move_y) + 0.01;
}

static void	handle_collectible(t_main_struct *ms)
{
	if (ms->map[(int)ms->player->y][(int)ms->player->x] == 'C')
	{
		play_sound(ms, SOUND_PICKUP);
		ms->map[(int)ms->player->y][(int)ms->player->x] = '0';
		ms->collectible_count = ms->collectible_count - 1;
		if (ms->collectible_count == 0)
			ms->died = 1;
		if (ms->fuel <= 0.9)
			ms->fuel = ms->fuel + 0.1;
		else
			ms->fuel = 1;
	}
}

void	one_direction(t_main_struct *ms, double move_x, double move_y)
{
	if (is_position_accessible(ms, (int)move_x, (int)move_y)
		&& is_position_accessible(ms, (int)ms->player->x, (int)move_y)
		&& is_position_accessible(ms, (int)move_x, (int)ms->player->y))
	{
		ms->player->x = move_x;
		ms->player->y = move_y;
	}
	else if (is_position_accessible(ms, (int)ms->player->x, (int)move_y))
	{
		adjust_horizontal_position(ms, move_x);
		ms->player->y = move_y;
	}
	else if (is_position_accessible(ms, (int)move_x, (int)ms->player->y))
	{
		ms->player->x = move_x;
		adjust_vertical_position(ms, move_y);
	}
	handle_collectible(ms);
}
