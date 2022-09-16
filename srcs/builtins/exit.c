//
//  exit.c
//  minishell_xcd
//
//  Created by Julia Demura on 26/08/2022.
//

#include "exit.h"
#include "builtin_utils.h"
#include <stdlib.h>

//noreturn void exit(int status); \
The exit() function causes normal process termination and the least significant byte of status (i.e., status & 0xFF) is returned to the parent (see wait(2)).
//https://man7.org/linux/man-pages/man3/exit.3.html


void	exit_builtin(t_env_struct *data, int status)
{
	write_str_fd("exit\n", data->fd_chosen);
	exit(status);
	
	//status − This is the status value returned to the parent process.

}
