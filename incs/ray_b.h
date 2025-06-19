#ifndef RAY_B_H
# define RAY_B_H

#include "structs_b.h"

typedef struct s_main_struct	t_main_struct;
typedef struct s_object_hit		t_object_hit;

double	*ray_check(t_main_struct *main_struct, \
	double (*cross)[5], double teta_cos_sin[2], \
	t_object_hit hit_tab[HIT_TAB_LEN]);
void	render_one_ray(t_main_struct *main_struct,
			double teta_cos_sin[2], int row, double teta);
#endif
