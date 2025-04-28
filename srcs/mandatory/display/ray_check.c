
#include "main_struct.h"
#include "math.h"
#include <stdio.h>
#include "common.h"
void ray_check(t_main_struct *main_struct, float (*cross)[3])
{
	float map_x;
	float map_y;
	float dir_x;
	float dir_y;
	float delta_x;
	float delta_y;
	float side_dist_x;
	float side_dist_y;
	float step_x;
	float step_y;

	map_x = main_struct->player->x;
	map_y = main_struct->player->y;
	dir_y = sin(main_struct->player->fov_angle);
	dir_x = cos(main_struct->player->fov_angle);
	if (fabsf(dir_x) < 0.0001)
		delta_x = 10000000;
	else
		delta_x = fabsf(1/dir_x);
	if (fabsf(dir_y) < 0.0001)
		delta_y = 10000000;
	else
		delta_y = fabsf(1/dir_y);
	if (dir_x > 0)
	{
		step_x = 1;
		side_dist_x = (floor(map_x) + 1 - main_struct->player->x) * delta_x;
	}
	else
	{
		step_x = -1;
		side_dist_x = (main_struct->player->x - floor(map_x)) * delta_x;
	}
	if (dir_y > 0)
	{
		step_y = 1;
		side_dist_y = (floor(map_y) + 1 - main_struct->player->y) * delta_y;
	}
	else
	{
		step_y = -1;
		side_dist_y = (main_struct->player->y - floor(map_y)) * delta_y;
	}
	if (fabsf(side_dist_x) < fabsf(side_dist_y))
		(*cross[2]) = 0;
	else
		(*cross[2]) = 1;
	while (main_struct->map[(int)floor(map_y)][(int)floor(map_x)] != '1')
	{
		if (fabsf(side_dist_x) < fabsf(side_dist_y))
		{
			side_dist_x = side_dist_x + delta_x;
			map_x = map_x + step_x;
			(*cross[2]) = 0;
		}
		else
		{
			side_dist_y = side_dist_y + delta_y;
			map_y = map_y + step_y;
			(*cross[2]) = 1;
		}
	}
	(*cross)[1] = map_y;
	(*cross)[0] = map_x;
	if ((*cross)[2] < 1)
		printf("dist_x is %f\n", fabs(side_dist_x));
	else
		printf("dist_y is %f\n", fabs(side_dist_y));
}
// float addy;
// float addx;
// int	i;
// (void)cross;
// i = 0;
// addy = 1 - 2 * (is_facing_up(main_struct->player->fov_angle));
// if (main_struct->player->fov_angle == 0 || main_struct->player->fov_angle == PI)
// 	addx = 0;
// else
// 	addx = 1 / tan(main_struct->player->fov_angle);
// printf("addx: %f, addy: %f\n", addx, addy);
// // while(i < 10)
// // {
// // 	(*cross)[1] = floor((*cross)[1]) + addy;
// // 	(*cross)[0] = (*cross)[0] + (main_struct->player->y - (*cross)[1]) * addx;
// // 	if ((*cross)[0] < 0 || (*cross)[1] < 0)
// // 		break;
// // 	printf("where am i -> (%f, %f)\n",(*cross)[0], (*cross)[1]);
// // 	// if (main_struct->map[(int)floor((*cross)[1])][(int)floor((*cross)[0])] == '1')
// // 	// 	break;
// // 	i++;
// // }