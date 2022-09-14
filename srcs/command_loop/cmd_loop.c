//
//  cmd_loop.c
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#include "cmd_loop.h"
#include "fd_management.h"
#include "built_in_set.h"
# include <unistd.h>
#include <stdlib.h>

#include <stdio.h>


///all exit 1 maybe need to be transfered into something more speaking

int	check_assess_to_file(const char *path)
{
	if (path == NULL)
		return (0);
	if (access(path, F_OK) < 0) ///	R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.
		return (-1);
	return (0);
}

int	not_exeption_do_pipe(int i, int comm_n, t_type type)
{
	if (type == BUILTIN && comm_n == 1) ///first and builtin - I do not pipe
		return (FLS);
	else if (i > 0 && i == comm_n - 1)///last - I do not pipe
		return (FLS);
	
	return (TRU);
}

char **	handle_one_param_set(int i, int comm_number, char **envp, t_param *param)
{
	char **new_envp;

	new_envp = NULL;
	if (not_exeption_do_pipe(i, comm_number, param->cmd.type) == TRU)
	{
		if (pipe(param->fd.pipe) < 0)
			exit(1);
	}
	param->child_pid = fork();
	if (param->child_pid < 0)
		exit(1);
	if (i == 0 && param->cmd.type == BUILTIN && comm_number == 1)
		new_envp = enviromental_variable_function(envp, param->cmd.command, param->cmd.cmd_args);
		
	if (param->child_pid == 0) ///child was created, we enter its process
	{
		if (check_assess_to_file(param->path_infile) < 0) ///check for file access for infile and in case of failure skip to next command
			exit(1);
		///	maybe I also skip command if its builtin but not the first one?
		pick_a_child(i, comm_number, param); ///pick_fd_for_child_function
		if (param->cmd.type == BUILTIN)
		{
			new_envp = enviromental_variable_function(envp, param->cmd.command, param->cmd.cmd_args); //TODO give them FDn to write into
		}
		else
		{
			execve(param->cmd.cmd_path, param->cmd.cmd_args, envp);
			 ///if kid fails and I need to update it in order to give err number
		}
		exit(1);
	}
	manage_parent_fd(i, comm_number, &param->fd);
	return (new_envp);
}

int	go_through_commands(t_exec *exec)
{
	int i;

	i = 0;
	while (exec->index < exec->comm_number)
	{
		exec->upd_envp = handle_one_param_set(i, exec->comm_number, exec->envp, exec[exec->index].params);
		if (exec->upd_envp != NULL)
		{
			free_array_of_str(exec->envp);
			exec->envp = exec->upd_envp;
			exec->upd_envp = NULL;
		}
		exec->index++;
		i++;
	}
	return (exec[exec->index].params->child_pid);
}
///	at the end I expect to receive sequence of pod_t in every t_param
///

void	loop_through_waitpid(int comm_num, t_param *params, int last_pid)
{
//	int i;
//	int wait_status;
//	int res_of_wait_status;
//
//	i = 0;
//	wait_status = -1;
//	res_of_wait_status = -1;
//	while (i < comm_num)
//	{
//		waitpid(params[i].child_pid, &wait_status, 0);
//		printf("\n%i/n", params[i].child_pid);
//		res_of_wait_status = WEXITSTATUS(wait_status); //not sure what this gives me
//		i++;
//	}
		int	status;
		int	p_id;
		int ex;

		p_id = last_pid;
		waitpid(p_id, &status, 0);

		if (WIFEXITED(status))
			ex = WEXITSTATUS(status);
}

t_exec	creat_exec_loop_commands(t_together *input, char **envp)
{
	t_exec exec;
	int ch_pid;

	exec = form_input_for_execution(envp, input);
	ch_pid = go_through_commands(&exec);
	loop_through_waitpid(exec.comm_number, exec.params, ch_pid);
	return (exec);
}
