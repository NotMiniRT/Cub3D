#include "common.h"
#include "lst_int.h"
#include "sound.h"
#include "structs_b.h"

int	get_status_door(int x, int y, t_main_struct *main_struct)
{
	int	i;

	i = 0;
	x++;
	y++;
	while (i < 100 && (*(main_struct->doors))[i][0] != 0)
	{
		if ((*(main_struct->doors))[i][0] == \
			y && (*(main_struct->doors))[i][1] == x)
			return ((*(main_struct->doors))[i][2]);
		i++;
	}
	return (-1);
}

void	activate_door_monster(t_main_struct *main_struct, int new_x, int new_y)
{
	int	i;

	if (main_struct->map[new_y][new_x] == 'D')
	{
		new_x++;
		new_y++;
		i = 0;
		while (i < 100 && (*(main_struct->doors))[i][0] != 0)
		{
			if ((*(main_struct->doors))[i][0] == \
				new_x && (*(main_struct->doors))[i][1] == new_y)
			{
				if ((*(main_struct->doors))[i][2] == 100)
					add_front_lst_int(main_struct->down_door, i);
				play_sound(main_struct, SOUND_DOOR);
				return ;
			}
			i++;
		}
	}
	return ;
}

static void	activate_door(t_main_struct *main_struct, int x, int y)
{
	int	new_x;
	int	new_y;
	int	i;

	new_x = (int)(main_struct->player->x + x) + 1;
	new_y = (int)(main_struct->player->y + y) + 1;
	if (main_struct->map[new_y - 1][new_x - 1] == 'D')
	{
		i = 0;
		while (i < 100 && (*(main_struct->doors))[i][0] != 0)
		{
			if ((*(main_struct->doors))[i][0] == \
				new_x && (*(main_struct->doors))[i][1] == new_y)
			{
				if ((*(main_struct->doors))[i][2] == 0)
					add_front_lst_int(main_struct->up_door, i);
				else if ((*(main_struct->doors))[i][2] == 100)
					add_front_lst_int(main_struct->down_door, i);
				play_sound(main_struct, SOUND_DOOR);
				return ;
			}
			i++;
		}
	}
	return ;
}

void	open_door(t_main_struct *main_struct)
{
	if (main_struct->player->fov_angle >= PIX6 && \
			main_struct->player->fov_angle < PIX3)
		activate_door(main_struct, 1, 1);
	else if (main_struct->player->fov_angle >= PIX3 && \
			main_struct->player->fov_angle < PIX23)
		activate_door(main_struct, 0, 1);
	else if (main_struct->player->fov_angle >= PIX23 && \
			main_struct->player->fov_angle < PIX56)
		activate_door(main_struct, -1, 1);
	else if (main_struct->player->fov_angle >= PIX56 && \
			main_struct->player->fov_angle < PIX76)
		activate_door(main_struct, -1, 0);
	else if (main_struct->player->fov_angle >= PIX76 && \
			main_struct->player->fov_angle < PIX43)
		activate_door(main_struct, -1, -1);
	else if (main_struct->player->fov_angle >= PIX43 && \
			main_struct->player->fov_angle < PIX53)
		activate_door(main_struct, 0, -1);
	else if (main_struct->player->fov_angle >= PIX53 && \
			main_struct->player->fov_angle < PIX116)
		activate_door(main_struct, 1, -1);
	else
		activate_door(main_struct, 1, 0);
}
