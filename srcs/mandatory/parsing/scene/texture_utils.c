#include <fcntl.h>
#include <unistd.h>

#include "libft.h"
#include "parsing.h"

char	*extract_texture_path(char *line, int id_len)
{
	char	*path;
	int		i;

	i = id_len;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path = ft_strdup(&line[i]);
	if (path == NULL)
		return (NULL);
	i = ft_strlen(path) - 1;
	while (i >= 0 && (path[i] == ' ' || path[i] == '\t' || path[i] == '\n'))
	{
		path[i] = '\0';
		i--;
	}
	return (path);
}

bool	is_texture_valid(char *path)
{
	int	fd;

	if (!path || !*path)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	if (check_extension(path, fd, XPM_FORMAT) == false)
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
