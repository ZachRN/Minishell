//
//  cmd_loop.c
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#include "cmd_loop.h"
#include "form_exec_struct.h"
# include <unistd.h>
#include <stdlib.h>


///all exit 1 maybe need to be transfered into something more speaking

void	check_assess_to_file(const char *path)
{
	
}

void	handle_one_param_set(int index, int comm_number, char **envp, t_param *param)
{
	//check if command is built-in
	
	if (pipe(param->fd.pipe) < 0)
		exit(1);
	param->child_pid = fork();
	if (param->child_pid < 0)
		exit(1);
	if (param->child_pid == 0) ///child was created, we enter its process
	{
		
		
		//	!!!	check for file access for infile and in case of failure skip to next command
		///	maybe I also skip command if its builtin but not the first one?
		
		
		
		//pick_fd_for_child_function
		
		execve(param->cmd.cmd_path, param->cmd.cmd_args, envp);
		exit(1); ///if kid fails and I need to update it in order to give err number
	}
	//pick_fd_for_parent_function
}

void	go_through_commands(t_exec *exec)
{
	while (exec->index < exec->comm_number)
	{
		handle_one_param_set(exec->index, exec->comm_number, exec->envp, exec[exec->index].params);
		exec->index++;
	}
	
}
///	at the end I expect to receive sequence of pod_t in every t_param

void	creat_exec_loop_commands(t_together *input, char **envp)
{
	t_exec exec;

	exec = form_input_for_execution(envp, input);
	
}
