/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:27:29 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 11:31:21 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_loop.h"
#include "built_in_set.h"
#include "path_search.h"
#include <unistd.h>
#include <stdlib.h>
#include "signal_handles.h"

//prev
// while (i < exec->comm_number)
// {
// 	free(exec->params[i].cmd.cmd_path);
// 	i++;
// }
void	free_exec_params(t_exec *exec)
{
	free(exec->params);
}

int	not_exeption_do_pipe(int i, int comm_n, t_type type)
{
	if (type == BUILTIN && comm_n == 1)
		return (FLS);
	else if (i == comm_n - 1)
		return (FLS);
	return (TRU);
}
