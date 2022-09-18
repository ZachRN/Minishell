#ifndef MESSY_H
# define MESSY_H

#include "structs.h"
#include "form_exec_struct.h"

char	**handle_one_param_set_two(t_exec *exec, int i, t_fd_two *fd);
void	zach_stuff(t_exec *exec, int i, t_fd_two *fd);
void	handle_child_fd(t_exec *exec, int i, t_fd_two *fd);
void	parent_pipe(t_exec *exec, int i, t_fd_two *fd);

#endif