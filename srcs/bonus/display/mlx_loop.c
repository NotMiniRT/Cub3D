#include "main_struct_b.h"
#include "display_b.h"
#include "timer.h"
#include "player_b.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
#include "doors_b.h"
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

// double cx = (*main_struct->items)[i][0] + 0.5;
// double cy = (*main_struct->items)[i][1] + 0.5;

// double dx = main_struct->player->x - cx;
// double dy = main_struct->player->y - cy;

// double angle = atan2(dy, dx);
// double angle_perp = angle + PI / 2.0;

// // Vecteur de base du sprite (non encore sécurisé)
// double ux = cos(angle_perp);
// double uy = sin(angle_perp);

// // Vecteur direction vers la caméra (pour dot product)
// double vx = dx;
// double vy = dy;
// double len_v = sqrt(vx * vx + vy * vy);
// if (len_v < 0.0001)
// 	len_v = 0.0001;
// vx /= len_v;
// vy /= len_v;

// // Produit scalaire
// double dot = ux * vx + uy * vy;

// // Si dot < 0 → vecteur perpendiculaire pointe "derrière" → on l’inverse
// if (dot < 0) {
// 	ux = -ux;
// 	uy = -uy;
// }

// // Segment
// double L = 0.5;
// double p1x = cx - ux * L;
// double p1y = cy - uy * L;
// double p2x = cx + ux * L;
// double p2y = cy + uy * L;



// static inline double dist_points(double x1, double y1, double x2, double y2)
// {
// 	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
// }

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
	p->x = center_x + dx * cos(0.0314) - dy * sin(0.0314);
	p->y = center_y + dx * sin(0.0314) + dy * cos(0.0314);
}

void update_items(t_main_struct *main_struct)
{
	int	i;
	int x;
	int y;
	i = 0;
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

int	mlx_loop_action(t_main_struct *main_struct)
{
	static int frame_count = 0;
	static clock_t last_time = 0;

	if (last_time == 0)
		last_time = clock();

	frame_count++;

	clock_t now = clock();
	double elapsed = (double)(now - last_time) / CLOCKS_PER_SEC;

	if (elapsed >= 1.0) {
		printf("FPS : %d\n", frame_count);
		frame_count = 0;
		last_time = now;
	}
	update_items(main_struct);
	if (frame_display(main_struct))
		return (1);
	if (timestamp_in_ms(main_struct) - main_struct->fuel_time > 700 && main_struct->fuel != 1)
	{
		main_struct->fuel_time = timestamp_in_ms(main_struct);
		main_struct->fuel--;
		if (main_struct->fuel == 0)
			main_struct->fuel = 1;
	}
	if (timestamp_in_ms(main_struct) - main_struct->last_move > 20
		&& is_moving(main_struct))
	{
		main_struct->last_move = timestamp_in_ms(main_struct);
		do_one_move(main_struct);
	}
	if (timestamp_in_ms(main_struct) - main_struct->door_action > 20
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


