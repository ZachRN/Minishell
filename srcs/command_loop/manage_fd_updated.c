/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage_fd_updated.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yuliia <yuliia@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 11:39:01 by yuliia        #+#    #+#                 */
/*   Updated: 2022/09/19 12:28:16 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "manage_fd_updated.h"
#include "built_in_set.h"
#include "path_search.h"
#include "signal_handles.h"
#include "struct.h"
#include "cmd_loop.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void	parent_pipe(t_exec *exec, int i, t_fd_two *fd)
{
	if (i != 0)
	{
		fd->storage = fd->pipe[0];
		fd->pipe[0] = -1;
	}
	if (i < exec->comm_number)
	{
		if (pipe(fd->pipe) < 0)
			exit(1);
	}
}

int	infile_or_heredoc(t_exec *exec)
{
	int	fd;

	fd = 0;
	if (exec->params[exec->index].in_flag == Infile)
	{
		fd = open(exec->params[exec->index].path_infile, O_RDONLY);
		if (fd < 0)
			perror_exit();
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (exec->params[exec->index].in_flag == Heredoc)
	{
		fd = open(exec->params[exec->index].heredoc, O_RDONLY);
		if (fd < 0)
			perror_exit();
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (fd);
}

int	check_infile_outfile(t_exec *exec)
{
	int	fd;

	fd = infile_or_heredoc(exec);
	if (exec->params[exec->index].append == 0)
	{
		fd = open(exec->params[exec->index].path_outfile, (O_TRUNC | O_WRONLY));
		if (fd < 0)
			perror_exit();
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (exec->params[exec->index].append == 1)
	{
		fd = open(exec->params[exec->index].path_outfile,
				(O_APPEND | O_WRONLY));
		if (fd < 0)
			perror_exit();
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (STDOUT_FILENO);
}

int	handle_child_fd(t_exec *exec, int i, t_fd_two *fd)
{
	if (fd->storage != -1)
	{
		dup2(fd->storage, STDIN_FILENO);
		close(fd->storage);
	}
	if (fd->pipe[1] != -1 && i != exec->comm_number - 1)
	{
		dup2(fd->pipe[1], STDOUT_FILENO);
		close(fd->pipe[1]);
	}
	else if (fd->pipe[1] != -1)
		close(fd->pipe[1]);
	if (fd->pipe[0] != -1)
		close(fd->pipe[0]);
	return (check_infile_outfile(exec));
}

void	closure(int i, t_exec *exec, t_fd_two *fd)
{
	if (i != 0)
	{
		close(fd->storage);
		fd->storage = -1;
	}
	if (exec->comm_number == 1)
	{
		close(fd->pipe[0]);
		close(fd->pipe[1]);
	}
	close(fd->pipe[1]);
	fd->pipe[1] = -1;
}
