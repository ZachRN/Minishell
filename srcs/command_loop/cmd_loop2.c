//
//  cmd_loop2.c
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#include "cmd_loop.h"
#include "fd_management.h"
#include "built_in_set.h"
#include "path_search.h"
# include <unistd.h>
#include <stdlib.h>
#include "signal_handles.h"

void	free_exec_params(t_exec *exec)
{
	int i;

	i = 0;
	while (i < exec->comm_number)
	{
		free(exec->params[i].cmd.cmd_path);
		i++;
	}
	free(exec->params);
}

int	not_exeption_do_pipe(int i, int comm_n, t_type type)
{
	if (type == BUILTIN && comm_n == 1) ///first and builtin - I do not pipe
		return (FLS);
	else if (i == comm_n - 1)///last - I do not pipe, got rid of i == 0
		return (FLS);
	return (TRU);
}
