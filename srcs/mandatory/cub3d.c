#include <stdlib.h>
#include "main_struct.h"
#include "common.h"
#include "display.h"
#include "libft.h"

#include "parsing.h"

int	main(int ac, char **av)
{
	t_main_struct	main_struct;
	t_infos			infos;

	ft_memset(&main_struct, 0, sizeof(t_main_struct));
	parsing(ac, av, &infos);
	start_display(&main_struct, &infos);
	free_main_struct(&main_struct);
	cleanup_parsing(&infos);
	return (EXIT_SUCCESS);
}
