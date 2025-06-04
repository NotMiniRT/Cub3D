#ifndef RAY_H
# define RAY_H

double	*ray_check(t_main_struct *main_struct,
			double (*cross)[5], double teta_cos_sin[2], t_object_hit	hit_tab[10]);
void	render_one_ray(t_main_struct *main_struct,
			double teta_cos_sin[2], int row, double teta);
#endif
