#include <stdlib.h>
#include <unistd.h>

#include "ft_dprintf.h"

void	exit_error(char *message)
{
	ft_dprintf(STDERR_FILENO, "%s", message);
	exit(EXIT_FAILURE);
}

void	free_array(char **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
