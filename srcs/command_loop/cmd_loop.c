/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:23:36 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 11:50:13 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_loop.h"
#include "built_in_set.h"
#include "path_search.h"
#include "signal_handles.h"
#include "manage_fd_updated.h"
#include "form_exec_struct.h"
#include <unistd.h>
#include <stdlib.h>


#include <stdio.h>

int	loop_through_waitpid(int last_pid)
{
	int	status;
	int	p_id;
	int	ex;

	ex = 0;
	p_id = last_pid;
	waitpid(p_id, &status, 0);
	if (WIFEXITED(status))
		ex = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		continue ;
	return (ex);
}


void	fork_handle_fd_execve(t_exec *exec, int i, t_fd_two *fd)
{
	exec->params[i].child_pid = fork();
	if (exec->params[i].child_pid < 0)
		exit(1);
	if (exec->params[i].child_pid == 0)
	{
		if (check_assess_to_file(exec->params[i].path_infile) < 0)
			exit(1);
		signal_director(DEFAULT_SIG);
		handle_child_fd(exec, i, fd);
		exec->params[i].cmd.cmd_path
			= find_command_path(exec->params[i].cmd, exec->envp);
		if (exec->params[i].cmd.type == BUILTIN)
			enviromental_variable_function(exec,
				exec->params[i].cmd.cmd_args, STDOUT_FILENO);
		else
			execve(exec->params[i].cmd.cmd_path,
				exec->params[i].cmd.cmd_args, exec->envp);
		exit(1);
	}
	closure(i, exec, fd);
}

	//WHEN IT IS ONLY ONE IT DOES NOT WRITE TO THE CORRECT AREA
	//IF IT IS A BUILT IN
char	**handle_one_param_set_two(t_exec *exec, int i, t_fd_two *fd)
{
	char	**new_envp;

	new_envp = NULL;

	if (exec->index == 0 && exec->params[i].cmd.type == BUILTIN
		&& exec->comm_number == 1)
	{
		close(fd->pipe[0]);
		close(fd->pipe[1]);
		return (enviromental_variable_function(exec,
				exec->params[i].cmd.cmd_args, STDOUT_FILENO));
	}
	else
		fork_handle_fd_execve(exec, i, fd);
	return (NULL);
}

t_exec	form_input_for_execution(char **envp, t_together *input)
{
	t_exec	exec;
	int		size_exec;

	size_exec = linked_list_size(input->head);
	exec.params = fill_exec_struct(input->head, size_exec);
	exec.comm_number = size_exec;
	exec.envp = envp;
	exec.index = 0;
	exec.upd_envp = NULL;
	return (exec);
}

t_exec	creat_exec_loop_commands(t_together *input, char **envp)
{
	t_exec		exec;
	t_fd_two	fd;

	exec = form_input_for_execution(envp, input);
	signal_director(PAUSE_SIG);
	fd.storage = -1;
	fd.pipe[0] = -1;
	fd.pipe[1] = -1;
	while (exec.index < exec.comm_number)
	{
		parent_pipe(&exec, exec.index, &fd);
		exec.upd_envp = handle_one_param_set_two(&exec, exec.index, &fd);
		exec.index++;
	}
	close(fd.pipe[0]);
	exec.last_error
		= loop_through_waitpid(exec.params[exec.index - 1].child_pid);
	signal_director(MAIN_SIG);
	free_exec_params(&exec);
	exec.params = NULL;
	return (exec);
}
