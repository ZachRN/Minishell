/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd_updated.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:45:42 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:46:14 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGE_FD_UPDATED_H
# define MANAGE_FD_UPDATED_H

# include "structs.h"
# include "form_exec_struct.h"

char	**handle_one_param_set_two(t_exec *exec, int i, t_fd_two *fd);
void	zach_stuff(t_exec *exec, int i, t_fd_two *fd);
int		handle_child_fd(t_exec *exec, int i, t_fd_two *fd);
void	parent_pipe(t_exec *exec, int i, t_fd_two *fd);
void	closure(int i, t_exec *exec, t_fd_two *fd);

#endif
