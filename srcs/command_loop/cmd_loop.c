//
//  cmd_loop.c
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#include "cmd_loop.h"
#include "fd_management.h"
#include "built_in_set.h"

#include "path_search.h"
#include "signal_handles.h"
# include <unistd.h>
#include <stdlib.h>


#include <stdio.h>

int	loop_through_waitpid(int comm_num, t_param *params, int last_pid)
{
	int	status;
	int	p_id;
	int ex;

	ex = 0;
	p_id = last_pid;
	waitpid(p_id, &status, 0);
	if (WIFEXITED(status))
		ex = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		continue;
	return (ex);
}

void	fork_and_manage_child(t_exec *exec, t_param *params, int i)
{
	params[i].child_pid = fork();
	if (params[i].child_pid < 0)
		exit(1);
	if (params[i].child_pid == 0)
	{
		if (check_assess_to_file(params[i].path_infile) < 0) ///in case of failure skip to next command
			exit(1);
		pick_a_child(i, exec->comm_number, params); ///pick_fd_for_child_function
		//in here next

		
		
		signal_director(DEFAULT_SIG);
		//exec->params[exec->index].cmd.cmd_path = find_command_path(exec->params[exec->index].cmd, exec->envp);
		params[i].cmd.cmd_path = find_command_path(params[i].cmd, exec->envp);
		if (params[i].cmd.type == BUILTIN)
			enviromental_variable_function(exec, params[i].cmd.cmd_args, params[i].fd);
		else
			execve(params[i].cmd.cmd_path, params[i].cmd.cmd_args, exec->envp);
		exit(1); ///if kid fails and I need to update it in order to give err number
	}
}

char	**handle_one_param_set(t_exec *exec, t_param *array_of_params, int i)
{
	char **new_envp;

	new_envp = NULL;
	if (not_exeption_do_pipe(exec->index, exec->comm_number, array_of_params[i].cmd.type) == TRU)
	{
		if (pipe(array_of_params[i].fd.pipe) < 0)
			exit(1);
	}
	if (exec->index == 0 && array_of_params[i].cmd.type == BUILTIN && exec->comm_number == 1)
	{
		new_envp = enviromental_variable_function(exec, array_of_params[i].cmd.cmd_args, array_of_params[i].fd);
		return (new_envp);
	}
	fork_and_manage_child(exec, array_of_params, i);
	manage_parent_fd(exec->index, exec->comm_number, &array_of_params[i].fd);
	return (new_envp);
}

t_exec	creat_exec_loop_commands(t_together *input, char **envp)
{
	t_exec exec;
	int ch_pid;
//task
	//make sure I treat indexes correctly with structs params
	
	
	exec = form_input_for_execution(envp, input); //++
	signal_director(PAUSE_SIG);
	while (exec.index < exec.comm_number)
	{
		exec.upd_envp = handle_one_param_set(&exec, exec.params, exec.index);
		exec.index++;
	}
	exec.last_error = loop_through_waitpid(exec.comm_number, exec.params, exec.params[exec.index - 1].child_pid);
	signal_director(MAIN_SIG);
	free_exec_params(&exec);
	exec.params = NULL;
	return (exec);
}
