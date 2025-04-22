#include <unistd.h>

#include "ft_dprintf.h"
#include "parsing.h"

void	exit_error(char *message)
{
	ft_dprintf(STDERR_FILENO, "%s", message);
	exit(EXIT_FAILURE);
}
