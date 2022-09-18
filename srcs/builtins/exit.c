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

int	is_num_neg(char *str)
{
	int i;
	int	negative;

	i = 0;
	negative = 0;
	while (str[i])
	{
		if (str[i] == '-')
			negative++;
		else if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		if (negative > 1)
			return (0);
		i++;
	}
	return (1);
}

int		write_error(char *str)
{
	write_str_fd("minishell: exit: ", STDERR_FILENO);
	write_str_fd(str, STDERR_FILENO);
	write_str_fd(": numeric arguement required\n", STDERR_FILENO);
	return (255);
}

void	exit_builtin(t_env_struct *data)
{
	int				number;
	char			*str;
	unsigned char	status;

	write_str_fd("exit\n", data->fd_chosen);
	str = "0";
	if (data->arguments)
		str = data->arguments[0];
	number = is_num_neg(str);
	if (number == 0)
		status = (unsigned char)write_error(str);
	else if (data->n_arguments > 1)
	{
		write_str_fd("minishell: exit: too many arguements\n", STDERR_FILENO);
		data->last_error = 1;
		return ;
	}
	else
		status = (unsigned char)ft_atoi(str);
	exit(status);
}
