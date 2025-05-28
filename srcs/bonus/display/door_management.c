#include "structs_b.h"
#include "common.h"
#include "stdio.h"


int	get_status_door(int x, int y, t_main_struct *main_struct)
{
	int i;

	i = 0;
	while (i < 100 && (*(main_struct->doors))[i][0] != 0)
	{
		if ((*(main_struct->doors))[i][0] == y + 1 && (*(main_struct->doors))[i][1] == x + 1)
			return ((*(main_struct->doors))[i][2]);
		i++;
	}
	return (-1);
}

/*
	TODO: understand what goes wrong with coordinates
*/
static void activate_door(t_main_struct *main_struct, int x, int y)
{
	int new_x;
	int new_y;
	int i;

	new_x = (int)(main_struct->player->x + x);
	new_y = (int)(main_struct->player->y + y);
	if (main_struct->map[new_y][new_x] == 'D')
	{
		i = 0;
		while (i < 100 && (*(main_struct->doors))[i][0] != 0)
		{
			if ((*(main_struct->doors))[i][0] == new_x + 1 && (*(main_struct->doors))[i][1] == new_y + 1)
			{
				if ((*(main_struct->doors))[i][2] == 0)
					(*(main_struct->doors))[i][2] = 100;
				else if ((*(main_struct->doors))[i][2] == 100)
					(*(main_struct->doors))[i][2] = 0;
				return ;
			}
			i++;
		}
	}
	return ;
}


void open_door(t_main_struct *main_struct)
{
	if (main_struct->player->fov_angle >= PIX6 && main_struct->player->fov_angle < PIX3)
		activate_door(main_struct, 1, 1);
	else if (main_struct->player->fov_angle >= PIX3 && main_struct->player->fov_angle < PIX23)
		activate_door(main_struct, 0, 1);
	else if (main_struct->player->fov_angle >= PIX23 && main_struct->player->fov_angle < PIX56)
		activate_door(main_struct, -1, 1);
	else if (main_struct->player->fov_angle >= PIX56 && main_struct->player->fov_angle < PIX76)
		activate_door(main_struct, -1, 0);
	else if (main_struct->player->fov_angle >= PIX76 && main_struct->player->fov_angle < PIX43)
		activate_door(main_struct, -1, -1);
	else if (main_struct->player->fov_angle >= PIX43 && main_struct->player->fov_angle < PIX53)
		activate_door(main_struct, 0, -1);
	else if (main_struct->player->fov_angle >= PIX53 && main_struct->player->fov_angle < PIX116)
		activate_door(main_struct, 1, -1);
	else
		activate_door(main_struct, 1, 0);
}