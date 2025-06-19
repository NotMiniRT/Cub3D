#include <limits.h>
#include <math.h>

#include "common.h"
#include "doors_b.h"
#include "image_b.h"
#include "libft.h"
#include "parsing.h"
#include "sound.h"
#include "structs_b.h"
#include "timer_b.h"

static inline double	dist_mamh(double xa, double xb, double ya, double yb)
{
	return (fabs(xa - xb) + fabs(ya - yb));
}

static int	is_position_walkable(t_main_struct *ms, double x, double y)
{
	if (ms->map[(int)y][(int)x] == '1')
		return (0);
	if (ms->map[(int)y][(int)x] == 'D'
		&& get_status_door(y, x, ms) != 0)
		return (0);
	return (1);
}

static void	check_cardinal_directions(t_main_struct *ms, \
		t_point *dir, int *dist, int *move)
{
	int		i;
	t_point	ndir;
	int		new_dist;

	i = -1;
	while (++i < 4)
	{
		ndir = (t_point){(double)("zyxy"[i] - 'y'), (double)("yzyx"[i] - 'y')};
		if (ms->map[(int)(ms->mj->y + ndir.y)][(int)(ms->mj->x + ndir.x)] == 'D'
			&& get_status_door(ms->mj->y + ndir.y, ms->mj->x + ndir.x, ms) == \
				100)
			activate_door_monster(ms, ms->mj->x + ndir.x, ms->mj->y + ndir.y);
		if (is_position_walkable(ms, ms->mj->x + ndir.x, ms->mj->y + ndir.y))
		{
			*move = 1;
			new_dist = dist_mamh(ms->mj->x + ndir.x, ms->player->x, \
				ms->mj->y + ndir.y, ms->player->y);
			if (new_dist < *dist)
			{
				*dist = new_dist;
				dir->x = (int)ndir.x;
				dir->y = (int)ndir.y;
			}
		}
	}
}

static void	check_diagonal_directions(t_main_struct *ms, \
		t_point *dir, int *dist, int *move)
{
	int		i;
	t_point	ndir;
	int		new_dist;

	i = 0;
	while (i < 4)
	{
		ndir = (t_point){(double)("zzxx"[i] - 'y'), (double)("zxzx"[i] - 'y')};
		if (is_position_walkable(ms, ms->mj->x + ndir.x, ms->mj->y + ndir.y)
			&& is_position_walkable(ms, ms->mj->x + ndir.x, ms->mj->y)
			&& is_position_walkable(ms, ms->mj->x, ms->mj->y + ndir.y))
		{
			*move = 1;
			new_dist = dist_mamh(ms->mj->x + ndir.x, ms->player->x, \
				ms->mj->y + ndir.y, ms->player->y);
			if (new_dist < *dist)
			{
				*dist = new_dist;
				dir->x = (int)ndir.x;
				dir->y = (int)ndir.y;
			}
		}
		i++;
	}
}

void	get_monster_dir(t_main_struct *ms)
{
	int		dist;
	int		move;
	t_point	dir;

	ms->mj->dir_time = timestamp_in_ms(ms);
	move = 0;
	dist = INT_MAX;
	dir = (t_point){0, 0};
	check_cardinal_directions(ms, &dir, &dist, &move);
	check_diagonal_directions(ms, &dir, &dist, &move);
	if (move == 1)
	{
		ms->mj->dir.x = dir.x;
		ms->mj->dir.y = dir.y;
	}
	else
	{
		ms->mj->dir.x = 0;
		ms->mj->dir.y = 0;
	}
}
