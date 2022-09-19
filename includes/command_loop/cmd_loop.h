/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_loop.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yuliia <yuliia@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 12:42:27 by yuliia        #+#    #+#                 */
/*   Updated: 2022/09/19 12:34:02 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LOOP_H
# define CMD_LOOP_H

# include "form_exec_struct.h"

t_exec	creat_exec_loop_commands(t_together *input, char **envp);

//in loop2
void	free_exec_params(t_exec *exec);
int		not_exeption_do_pipe(int i, int comm_n, t_type type);
void	perror_exit(void);
int		get_fd_for_builtin(t_exec *exec);

#endif /* cmd_loop_h */
