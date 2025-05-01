
#include "main_struct.h"
#include "math.h"
#include <stdio.h>
#include "common.h"

void ray_check(t_main_struct *main_struct, double (*cross)[2], double teta_cos_sin[2])
{
    int map_x;
    int map_y;
    double dir_x;
    double dir_y;
    double delta_x;
    double delta_y;
    double side_dist_x;
    double side_dist_y;
    double dist;
    int step_x;
    int step_y;
    int side;

    double player_x = main_struct->player->x;
    double player_y = main_struct->player->y;

    map_x = (int)floor(player_x);
    map_y = (int)floor(player_y);

    dir_x = teta_cos_sin[0];
    dir_y = teta_cos_sin[1];

    if (fabs(dir_x) < 0.0001)
        delta_x = 1e30;
    else 
        delta_x = fabs(1.0 / dir_x);
    if (fabs(dir_y) < 0.0001)
        delta_y = 1e30;
    else 
        delta_y = fabs(1.0 / dir_y);

    if (dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (player_x - map_x) * delta_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - player_x) * delta_x;
    }
    
    if (dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (player_y - map_y) * delta_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - player_y) * delta_y;
    }

    side = 0;
    while (main_struct->map[map_y][map_x] != '1')
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_y;
            map_y += step_y;
            side = 1;
        }
    }

    if (side == 0)
    {
        double wall_x = player_x + (map_x - player_x + (1 - step_x) * 0.5);
        double wall_y = player_y + ((map_x - player_x + (1 - step_x) * 0.5) / dir_x) * dir_y;
        
        dist = sqrt(pow(wall_x - player_x, 2) + pow(wall_y - player_y, 2));
    }
    else
    {
        double wall_x = player_x + ((map_y - player_y + (1 - step_y) / 2) / dir_y) * dir_x;
        double wall_y = player_y + (map_y - player_y + (1 - step_y) / 2);

        dist = sqrt(pow(wall_x - player_x, 2) + pow(wall_y - player_y, 2));
    }

    (*cross)[0] = dist;
    (*cross)[1] = side;
}

    // printf("First colision is in (%d, %d), on axis %c\n", 
    //        map_x, map_y, 
    //        (side == 0) ? 'x' : 'y');
    // printf("player: x: %f, y: %f, angle: %f\n", 
    //        player_x, player_y, 
    //        main_struct->player->fov_angle);
    // printf("dist_%c is %f\n", 
    //        (side == 0) ? 'x' : 'y', 
    //        dist);

// void ray_check(t_main_struct *main_struct, double (*cross)[3])
// {
// 	double map_x;
// 	double map_y;
// 	double dir_x;
// 	double dir_y;
// 	double delta_x;
// 	double delta_y;
// 	double side_dist_x;
// 	double side_dist_y;
// 	double step_x;
// 	double step_y;

// 	map_x = main_struct->player->x;
// 	map_y = main_struct->player->y;
// 	dir_y = sin(main_struct->player->fov_angle);
// 	dir_x = cos(main_struct->player->fov_angle);
// 	if (fabsf(dir_x) < 0.0001)
// 		delta_x = 100000;
// 	else
// 		delta_x = fabsf(1/dir_x);
// 	if (fabsf(dir_y) < 0.0001)
// 		delta_y = 100000;
// 	else
// 		delta_y = fabsf(1/dir_y);
// 	if (dir_x > 0)
// 	{
// 		step_x = 1;
// 		side_dist_x = (floor(map_x) + 1 - main_struct->player->x) * delta_x;
// 	}
// 	else
// 	{
// 		step_x = -1;
// 		side_dist_x = (main_struct->player->x - floor(map_x)) * delta_x;
// 	}
// 	if (dir_y > 0)
// 	{
// 		step_y = 1;
// 		side_dist_y = (floor(map_y) + 1 - main_struct->player->y) * delta_y;
// 	}
// 	else
// 	{
// 		step_y = -1;
// 		side_dist_y = (main_struct->player->y - floor(map_y)) * delta_y;
// 	}
// 	if (fabsf(side_dist_x) < fabsf(side_dist_y))
// 		(*cross[2]) = 0;
// 	else
// 		(*cross[2]) = 1;
// 	while (main_struct->map[(int)floor(map_y)][(int)floor(map_x)] != '1')
// 	{
// 		if (fabsf(side_dist_x) < fabsf(side_dist_y))
// 		{
// 			side_dist_x = side_dist_x + delta_x;
// 			map_x = map_x + step_x;
// 			(*cross[2]) = 0;
// 		}
// 		else
// 		{
// 			side_dist_y = side_dist_y + delta_y;
// 			map_y = map_y + step_y;
// 			(*cross[2]) = 1;
// 		}
// 	}
// 	(*cross)[1] = map_y;
// 	(*cross)[0] = map_x;
// 	if ((*cross)[2] < 1)
// 		printf("dist_x is %f\n", (map_x - main_struct->player->x + (1 - step_x) / 2) / dir_x);
// 	else
// 		printf("dist_y is %f\n", (map_y - main_struct->player->y + (1 - step_y) / 2) / dir_y);
// }
// double addy;
// double addx;
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