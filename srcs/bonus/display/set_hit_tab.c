#include "common.h"
#include "doors_b.h"
#include "structs_b.h"

static void	door_calc(t_object_hit *obj_hit,
	t_main_struct *main_struct, int row, double teta_cos_sin[2])
{
	obj_hit->status = get_status_door(obj_hit->map_x, obj_hit->map_y,
			main_struct);
	obj_hit->height = (WINDOW_HEIGHT
			/ (obj_hit->dist * main_struct->cos_r_h_tab[row]));
	if ((obj_hit->side == 0 && teta_cos_sin[0] < 0)
		|| (obj_hit->side == 1 && teta_cos_sin[1] > 0))
		obj_hit->wall_pc = 1 - obj_hit->wall_pc ;
	obj_hit->text_x = main_struct->door->size * obj_hit->wall_pc ;
	if (obj_hit->text_x < 0)
		obj_hit->text_x = 0;
	if (obj_hit->text_x >= main_struct->door->size)
		obj_hit->text_x = main_struct->door->size - 1;
	obj_hit->step = main_struct->door->size / obj_hit->height;
	obj_hit->text_y_index = -(WINDOW_HEIGHT - obj_hit->height)
		* 0.5 * obj_hit->step;
	obj_hit->height_check_minus = (WINDOW_HEIGHT
			- obj_hit->height) * 0.5;
	obj_hit->height_check_plus = (WINDOW_HEIGHT
			+ obj_hit->height) * 0.5;
	obj_hit->line_add = (int *)(main_struct->door->buffer
			+ (obj_hit->text_x * main_struct->door->line_bytes));
	obj_hit->dark_factor = (1 - (obj_hit->dist / (main_struct->fuel
					* RENDER_DIST)));
}

static void	item_calc(t_object_hit *obj_hit,
	t_main_struct *main_struct, int row)
{
	obj_hit->height = (WINDOW_HEIGHT
			/ (obj_hit->dist * main_struct->cos_r_h_tab[row]));
	obj_hit->text_x = main_struct->potion->size * obj_hit->wall_pc;
	if (obj_hit->text_x < 0)
		obj_hit->text_x = 0;
	if (obj_hit->text_x >= main_struct->potion->size)
		obj_hit->text_x = main_struct->potion->size - 1;
	obj_hit->step = main_struct->potion->size / obj_hit->height;
	obj_hit->text_y_index = -(WINDOW_HEIGHT - obj_hit->height)
		* 0.5 * obj_hit->step;
	obj_hit->height_check_minus = (WINDOW_HEIGHT
			- obj_hit->height) * 0.5;
	obj_hit->height_check_plus = (WINDOW_HEIGHT
			+ obj_hit->height) * 0.5;
	obj_hit->line_add = (int *)(main_struct->potion->buffer
			+ (obj_hit->text_x * main_struct->potion->line_bytes));
	obj_hit->status = 1;
	obj_hit->dark_factor
		= (1 - (obj_hit->dist / (main_struct->fuel * RENDER_DIST)));
}

static void	mj_calc(t_object_hit *obj_hit,
	t_main_struct *main_struct, int row)
{
	obj_hit->height = (WINDOW_HEIGHT
			/ (obj_hit->dist * main_struct->cos_r_h_tab[row]));
	obj_hit->text_x = (main_struct->mj->sprite[main_struct->mj->frame])->size
		* obj_hit->wall_pc;
	if (obj_hit->text_x < 0)
		obj_hit->text_x = 0;
	if (obj_hit->text_x
		>= (main_struct->mj->sprite[main_struct->mj->frame])->size)
		obj_hit->text_x
			= (main_struct->mj->sprite[main_struct->mj->frame])->size - 1;
	obj_hit->step = (main_struct->mj->sprite[main_struct->mj->frame])->size
		/ obj_hit->height;
	obj_hit->text_y_index = -(WINDOW_HEIGHT - obj_hit->height)
		* 0.5 * obj_hit->step;
	obj_hit->height_check_minus = (WINDOW_HEIGHT
			- obj_hit->height) * 0.5;
	obj_hit->height_check_plus = (WINDOW_HEIGHT
			+ obj_hit->height) * 0.5;
	obj_hit->line_add
		= (int *)((main_struct->mj->sprite[main_struct->mj->frame])->buffer
			+ (obj_hit->text_x * (main_struct->mj->sprite[main_struct->mj->\
					frame])->line_bytes));
	obj_hit->status = 1;
	obj_hit->dark_factor = (1
			- (obj_hit->dist / (main_struct->fuel * RENDER_DIST)));
}

void	set_hit_tab(t_render_calculus *render_calc,
	t_main_struct *main_struct, int row, double teta_cos_sin[2])
{
	int	i;

	i = 0;
	while (i < render_calc->res[4])
	{
		if (render_calc->hit_tab[i].type == DOOR)
			door_calc(&render_calc->hit_tab[i], main_struct, row, teta_cos_sin);
		else if (render_calc->hit_tab[i].type == ITEM)
			item_calc(&render_calc->hit_tab[i], main_struct, row);
		else if (render_calc->hit_tab[i].type == MONSTER)
			mj_calc(&render_calc->hit_tab[i], main_struct, row);
		i++;
	}
}
