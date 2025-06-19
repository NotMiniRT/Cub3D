#ifndef RAY_H
# define RAY_H

# include "structs_b.h"

typedef struct s_main_struct	t_main_struct;

double	*ray_check(t_main_struct *main_struct,
			double (*cross)[4], double teta_cos_sin[2]);
void	render_one_ray(t_main_struct *main_struct,
			double teta_cos_sin[2], int row, double teta);
void	get_calcul_param(t_render_calculus *render_calc,
	t_main_struct *main_struct, double teta_cos_sin[2], int row);
int	put_transparency(t_render_calculus *render_calc,
		t_main_struct *main_struct, int row, int j);
void	add_hit_ray_door(t_ray_calculus *calcul,
	t_object_hit hit_tab[HIT_TAB_LEN],
	t_main_struct *main_struct, double cos_sin[2]);
void	add_hit_ray_item(t_ray_calculus *calcul,
	t_object_hit hit_tab[HIT_TAB_LEN],
	t_main_struct *main_struct, double cos_sin[2]);
double	get_monster_dist(t_ray_calculus *calcul,
	t_main_struct *main_struct, double cos_sin[2]);
void	add_mj(t_ray_calculus *calcul, t_object_hit	hit_tab[HIT_TAB_LEN]);

#endif
