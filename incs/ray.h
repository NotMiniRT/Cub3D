#ifndef RAY_H
# define RAY_H

double	*ray_check(t_main_struct *main_struct,
			double (*cross)[4], double teta_cos_sin[2]);
void	render_one_ray(t_main_struct *main_struct,
			double teta_cos_sin[2], int row, double teta);

#endif
