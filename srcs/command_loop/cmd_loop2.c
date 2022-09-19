/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_loop2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yuliia <yuliia@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 11:27:29 by yuliia        #+#    #+#                 */
/*   Updated: 2022/09/19 12:38:21 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_loop.h"
#include "built_in_set.h"
#include "path_search.h"
#include "signal_handles.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	free_exec_params(t_exec *exec)
{
	free(exec->params);
}

int	not_exeption_do_pipe(int i, int comm_n, t_type type)
{
	if (type == BUILTIN && comm_n == 1)
		return (FLS);
	else if (i == comm_n - 1)
		return (FLS);
	return (TRU);
}

void	perror_exit(void)
{
	perror("minishell");
	exit(1);
}

int	get_fd_for_builtin(t_exec *exec)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (exec->params[exec->index].append == 0)
		fd = open(exec->params[exec->index].path_outfile, (O_TRUNC | O_WRONLY));
	else if (exec->params[exec->index].append == 1)
		fd = open(exec->params[exec->index].path_outfile,
				(O_APPEND | O_WRONLY));
	return (fd);
}
