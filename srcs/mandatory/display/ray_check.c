#include "main_struct.h"
#include "math.h"
#include <stdio.h>
#include "common.h"

void ray_check(t_main_struct *main_struct, double (*cross)[3], double teta_cos_sin[2])
{
	double dir_x;
    double dir_y;

	double player_x;
    double player_y;

    double delta_x;
    double delta_y;

    double side_dist_x;
    double side_dist_y;

    int step_x;
    int step_y;

	int side;

	int map_x;
    int map_y;

	double wall_x;
    double wall_y;

	double dist;

	player_x = main_struct->player->x;
    player_y = main_struct->player->y;
	dir_x = teta_cos_sin[0];
    dir_y = teta_cos_sin[1];

    map_x = (int)floor(player_x);
    map_y = (int)floor(player_y);

	if (fabs(dir_x) < 0.000001)
		delta_x = 10000000;
	else 
		delta_x = fabs(1.0 / dir_x);
	if (fabs(dir_y) < 0.000001)
		delta_y = 10000000;
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
        wall_x = (map_x - player_x + (1 - step_x) * 0.5);
        wall_y = ((map_x - player_x + (1 - step_x) * 0.5) / dir_x) * dir_y;
        
        dist = sqrt(pow(wall_x, 2) + pow(wall_y, 2));
    }
    else
    {
        wall_x = ((map_y - player_y + (1 - step_y) / 2) / dir_y) * dir_x;
        wall_y = (map_y - player_y + (1 - step_y) / 2);

        dist = sqrt(pow(wall_x, 2) + pow(wall_y, 2));
    }

    (*cross)[0] = dist;
    (*cross)[1] = side;
    if (side == 1)
        (*cross)[2] = player_x + wall_x;
    else
        (*cross)[2] = player_y + wall_y;
}