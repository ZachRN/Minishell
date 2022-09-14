//
//  cmd_loop.c
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#include "cmd_loop.h"
#include "form_exec_struct.h"
#include "fd_management.h"
# include <unistd.h>
#include <stdlib.h>


///all exit 1 maybe need to be transfered into something more speaking

int	check_assess_to_file(const char *path)
{
	///	R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.
	if (access(path, R_OK) < 0)
		return (-1);
	return (0);
}

void	handle_one_param_set(int i, int comm_number, char **envp, t_param *param)
{
	//TODO check if command is built-in
	
	if (i == comm_number - 1) ///last command I do not pipe
	{
		if (pipe(param->fd.pipe) < 0)
			exit(1);
	}
	
	param->child_pid = fork();
	if (param->child_pid < 0)
		exit(1);
	if (param->child_pid == 0) ///child was created, we enter its process
	{
		if (check_assess_to_file(param->path_infile) < 0) ///check for file access for infile and in case of failure skip to next command
			return ;
		///	maybe I also skip command if its builtin but not the first one?
		pick_a_child(i, comm_number, param); ///pick_fd_for_child_function
		execve(param->cmd.cmd_path, param->cmd.cmd_args, envp);
		exit(1); ///if kid fails and I need to update it in order to give err number
	}
	manage_parent_fd(i, comm_number, &param->fd);
}

void	go_through_commands(t_exec *exec)
{
	int i;

	i = 0;
	while (exec->index < exec->comm_number)
	{
		handle_one_param_set(i, exec->comm_number, exec->envp, exec[exec->index].params); //make sure comm number is NUMBER of commands I receive
		exec->index++;
		i++;
	}
	
}
///	at the end I expect to receive sequence of pod_t in every t_param

void	creat_exec_loop_commands(t_together *input, char **envp)
{
	t_exec exec;

	exec = form_input_for_execution(envp, input);
	
}
