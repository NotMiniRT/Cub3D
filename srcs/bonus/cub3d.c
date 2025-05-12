#include <stdlib.h>
#include "main_struct.h"
#include "common.h"
#include "display.h"
#include "parsing.h"

int	main(int ac, char **av)
{
	t_main_struct main_struct;
	parsing(ac, av);
	exit(1);
	init_main_struct(&main_struct);
	start_display(&main_struct);
	free_main_struct(&main_struct);
	return (EXIT_SUCCESS);
}
