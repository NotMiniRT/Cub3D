#ifndef DISPLAY_B_H
# define DISPLAY_B_H

# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;
typedef struct s_infos			t_infos;

int		frame_display(t_main_struct *main_struct);
int		mlx_loop_action(t_main_struct *main_struct);

bool	start_display(t_main_struct *main_struct, t_infos *infos);
bool	init_all_sprites(t_main_struct *main_struct, t_infos *infos);

#endif
