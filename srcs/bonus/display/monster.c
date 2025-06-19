#include <math.h>

#include "common.h"
#include "doors_b.h"
#include "image_b.h"
#include "libft.h"
#include "parsing.h"
#include "sound.h"
#include "structs_b.h"
#include "timer_b.h"

static bool get_mj_sprites(t_main_struct *main_struct)
{
	int i;
	char *name;

	main_struct->mj->sprite = malloc(sizeof(t_image_cub *) * 36);
	if (main_struct->mj->sprite == NULL)
		return (false);
	i = 0;
	while (i < MJ_SPRITES)
	{
		name = ft_strjoin_free2(ft_strjoin_free("assets/textures/mj/mj-", ft_itoa(i)), ".xpm");
		if (!get_image_cub_from_xpm(main_struct, &((main_struct->mj->sprite)[i]), name, 256))
		{
			free(name);
			(main_struct->mj->sprite)[i] = NULL;
			return (false);
		}
		free(name);
		i++;
	}
	return (true);
}

bool set_mj(t_main_struct *main_struct, t_infos *infos)
{
	main_struct->mj = malloc(sizeof(t_monster));
	if (main_struct->mj == NULL)
		return (false);
	main_struct->mj->frame = 0;
	main_struct->mj->move_time = 0;
	main_struct->mj->dir_time = 0;
	if (!get_mj_sprites(main_struct))
		return (false);
	main_struct->mj->dir.x = 0;
	main_struct->mj->dir.y = 0;
	main_struct->mj->p1.x = 0;
	main_struct->mj->p1.y = 0;
	main_struct->mj->p2.x = 0;
	main_struct->mj->p2.y = 0;
	main_struct->mj->x = (double)(infos->scene->monster_positions[0] - 0.5);
	main_struct->mj->y = (double)(infos->scene->monster_positions[1] - 0.5);
	return (true);
}

static inline double dist_mamh(double xa, double xb, double ya ,double yb)
{
	return (fabs(xa- xb) + fabs(ya - yb));
}
void get_monster_dir(t_main_struct *main_struct)
{
	int i;
	int dist;
	int move;
	t_point dir;
	t_point ndir;

	main_struct->mj->dir_time = timestamp_in_ms(main_struct);
	i = 0;
	move = 0;
	dist = 2147483647;
	while (i < 4)
	{
		ndir = (t_point){(double)("zyxy"[i] - 'y'), (double)("yzyx"[i] - 'y')};
		if ((main_struct->map[(int)(main_struct->mj->y + ndir.y)][(int)(main_struct->mj->x + ndir.x)] == 'D'
			&& get_status_door(main_struct->mj->y + ndir.y, main_struct->mj->x + ndir.x, main_struct) == 100))
			activate_door_monster(main_struct, main_struct->mj->x + ndir.x, main_struct->mj->y + ndir.y);
		if (main_struct->map[(int)(main_struct->mj->y + ndir.y)][(int)(main_struct->mj->x + ndir.x)] != '1'
			&& (main_struct->map[(int)(main_struct->mj->y + ndir.y)][(int)(main_struct->mj->x + ndir.x)] != 'D'
				|| get_status_door(main_struct->mj->y + ndir.y, main_struct->mj->x + ndir.x, main_struct) == 0))
		{
			move = 1;
			if (dist_mamh(main_struct->mj->x + ndir.x, main_struct->player->x, \
				main_struct->mj->y + ndir.y, main_struct->player->y) < dist)
			{
				dist = dist_mamh(main_struct->mj->x + ndir.x, main_struct->player->x, \
					main_struct->mj->y + ndir.y, main_struct->player->y);
				dir.x = (int)ndir.x;
				dir.y = (int)ndir.y;
			}
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		ndir = (t_point){(double)("zzxx"[i] - 'y'), (double)("zxzx"[i] - 'y')};
		if ((main_struct->map[(int)(main_struct->mj->y + ndir.y)][(int)(main_struct->mj->x + ndir.x)] != '1'
			&& (main_struct->map[(int)(main_struct->mj->y + ndir.y)][(int)(main_struct->mj->x + ndir.x)] != 'D'
				|| get_status_door(main_struct->mj->y + ndir.y, main_struct->mj->x + ndir.x, main_struct) == 0))
			&& (main_struct->map[(int)(main_struct->mj->y)][(int)(main_struct->mj->x + ndir.x)] != '1'
			&& (main_struct->map[(int)(main_struct->mj->y)][(int)(main_struct->mj->x + ndir.x)] != 'D'
					|| get_status_door(main_struct->mj->y, main_struct->mj->x + ndir.x, main_struct) == 0))
			&& (main_struct->map[(int)(main_struct->mj->y + ndir.y)][(int)(main_struct->mj->x)] != '1'
			&& (main_struct->map[(int)(main_struct->mj->y + ndir.y)][(int)(main_struct->mj->x)] != 'D'
				|| get_status_door(main_struct->mj->y + ndir.y, main_struct->mj->x, main_struct) == 0)))
		{
			move = 1;
			if (dist_mamh(main_struct->mj->x + ndir.x, main_struct->player->x, \
				main_struct->mj->y + ndir.y, main_struct->player->y) < dist)
			{
				dist = dist_mamh(main_struct->mj->x + ndir.x, main_struct->player->x, \
					main_struct->mj->y + ndir.y, main_struct->player->y);
				dir.x = (int)ndir.x;
				dir.y = (int)ndir.y;
			}
		}
		i++;
	}
	main_struct->mj->dir.x = dir.x;
	main_struct->mj->dir.y = dir.y;
	if (move == 1)
		return ;
	main_struct->mj->dir.x = 0;
	main_struct->mj->dir.y = 0;
}

void move_monster(t_main_struct *main_struct)
{
	static int i = 0;
	
	if (i == 0)
		get_monster_dir(main_struct);
	main_struct->mj->move_time = timestamp_in_ms(main_struct);
	main_struct->mj->x = main_struct->mj->x + main_struct->mj->dir.x * 0.1;
	main_struct->mj->y = main_struct->mj->y + main_struct->mj->dir.y * 0.1;
	if ((fabs(main_struct->mj->x - main_struct->player->x) + fabs(main_struct->mj->y - main_struct->player->y)) <= 1)
	{
		main_struct->died = 1;
		play_sound(main_struct, SOUND_DEATH);
		return ;
	}
	if (i % 3 == 0)
	{
		if (main_struct->mj->frame == 20)
			play_sound(main_struct, SOUND_MJ);
		main_struct->mj->frame = main_struct->mj->frame + 1;
		if (main_struct->mj->frame >= MJ_SPRITES)
			main_struct->mj->frame = 0;
	}
	if (i >= 9)
		i = 0;
	else
		i++;
}
