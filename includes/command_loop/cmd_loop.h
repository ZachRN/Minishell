//
//  cmd_loop.h
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#ifndef cmd_loop_h
#define cmd_loop_h

#include "form_exec_struct.h"

t_exec	creat_exec_loop_commands(t_together *input, char **envp);

//in loop2
void	free_exec_params(t_exec *exec);
int		not_exeption_do_pipe(int i, int comm_n, t_type type);

#endif /* cmd_loop_h */

