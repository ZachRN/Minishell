/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:17:46 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 11:24:48 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin_utils.h"

//https://www.geeksforgeeks.org/c-program-print-environment-variables/

int	env_builtin(char **env_arg, int fd)
{
	int	i;

	i = 0;
	while (env_arg[i] != NULL)
	{
		write_str_fd(env_arg[i], fd);
		write_one_char_fd(fd, '\n');
		i++;
	}
	return (0);
}
