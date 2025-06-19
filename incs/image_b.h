#ifndef IMAGE_B_H
# define IMAGE_B_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;
typedef struct s_image_cub		t_image_cub;

# define SUCCESS_LOAD "✓ Successfully loaded %s%s\n"
# define ERROR_LOAD "✗ Error loading %s%s\n"

# define S_WALL_TEXTURE "south wall texture"
# define W_WALL_TEXTURE "west wall texture"
# define N_WALL_TEXTURE "north wall texture"
# define E_WALL_TEXTURE "east wall texture"

# define FRAME_BUFFER "frame buffer"

# define FOG_ASSET "assets/textures/walls/fog.xpm"
# define FOG_TEXTURE "fog texture"

# define DOOR_TEXTURE "assets/textures/walls/door6.xpm"
# define DOOR_ASSET "door texture"

# define POTION_ASSET "assets/textures/walls/potion.xpm"
# define POTION_TEXTURE "potion texture"

# define MINIMAP_MESSAGE "minimap"
# define FUEL_BAR_MESSAGE "fuel bar"


int		create_img_cub(t_main_struct *main_struct,
			t_image_cub **img, int x, int y);
int		get_image_cub_from_xpm(t_main_struct *main_struct,
			t_image_cub **img, char *path, int size);
int		get_color(t_image_cub *img, int texture_x, int texture_y);
void	free_image_cub(t_main_struct *main_struct, t_image_cub *img);
void	change_pixel_color(t_image_cub *img, int color, int x, int y);
int		get_image_cub_from_xpm_no_rot(t_main_struct *main_struct, \
									t_image_cub **img, char *path, int size);

#endif
