//
//  cmd_loop.c
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#include "cmd_loop.h"
#include "built_in_set.h"

#include "path_search.h"
#include "signal_handles.h"
# include <unistd.h>
#include <stdlib.h>

#include "messy.h"

#include <stdio.h>

int	loop_through_waitpid(int last_pid)
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

t_exec	creat_exec_loop_commands(t_together *input, char **envp)
{
	t_exec exec;
	t_fd_two fd;
	
	exec = form_input_for_execution(envp, input); //++
	signal_director(PAUSE_SIG);
	fd.storage = -1;
	fd.pipe[0] = -1;
	fd.pipe[1] = -1;
	while (exec.index < exec.comm_number)
	{
		// exec.upd_envp = handle_one_param_set(&exec, exec.params, exec.index);
		parent_pipe(&exec, exec.index, &fd);
		exec.upd_envp = handle_one_param_set_two(&exec, exec.index, &fd);
		exec.index++;
	}
	close(fd.pipe[0]);
	exec.last_error = loop_through_waitpid(exec.params[exec.index - 1].child_pid);
	signal_director(MAIN_SIG);
	free_exec_params(&exec);
	exec.params = NULL;
	return (exec);
}
