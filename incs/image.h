#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_main_struct	t_main_struct;
typedef struct s_image_cub		t_image_cub;

# define FOG_ASSET "assets/textures/walls/fog.xpm"

int		create_img_cub(t_main_struct *main_struct,
			t_image_cub **img, int x, int y);
int		get_image_cub_from_xpm(t_main_struct *main_struct,
			t_image_cub **img, char *path);
int		get_color(t_image_cub *img, int texture_x, int texture_y);
void	free_image_cub(t_main_struct *main_struct, t_image_cub *img);
void	change_pixel_color(t_image_cub *img, int color, int x, int y);

#endif
