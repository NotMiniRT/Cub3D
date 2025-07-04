/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:46 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:48:22 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sound.h"

static void	close_extra_fds(int keep_fd)
{
	int	max_fd;
	int	fd;

	max_fd = sysconf(_SC_OPEN_MAX);
	fd = 3;
	while (fd < max_fd)
	{
		if (fd != keep_fd)
			close(fd);
		fd++;
	}
}

void	setup_child_process(int pipefd[2])
{
	FILE	*devnull;

	close_extra_fds(pipefd[1]);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	devnull = fopen(DEV_NULL, TRUNCATE);
	if (devnull)
	{
		if (dup2(fileno(devnull), STDERR_FILENO) == -1)
		{
			close(pipefd[1]);
			return ;
		}
		fclose(devnull);
	}
	close(pipefd[1]);
}

pid_t	create_child_process(int pipefd[2])
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (pid);
}
