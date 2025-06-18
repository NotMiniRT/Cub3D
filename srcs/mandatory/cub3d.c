#include "display.h"
#include "ft_dprintf.h"
#include "libft.h"

int	main(int ac, char **av)
{
	t_main_struct	main_struct;
	t_infos			infos;

	ft_memset(&main_struct, 0, sizeof(t_main_struct));
	ft_memset(&infos, 0, sizeof(t_infos));
	parsing(ac, av, &infos);
	if (!start_display(&main_struct, &infos))
		ft_dprintf(2, "Error\nExternal function fail during initialisation\n");
	free_main_struct(&main_struct);
	cleanup_parsing(&infos);
	return (EXIT_SUCCESS);
}
