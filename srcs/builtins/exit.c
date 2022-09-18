/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:17:53 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 11:24:50 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "builtin_utils.h"
#include <stdlib.h>

//noreturn void exit(int status); 
//The exit() function causes normal process termination
//and the least significant byte of status (i.e., status & 0xFF)
//is returned to the parent (see wait(2)).
//https://man7.org/linux/man-pages/man3/exit.3.html

void	exit_builtin(t_env_struct *data, int status)
{
	write_str_fd("exit\n", data->fd_chosen);
	exit(status);
}
