/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_get_cmd.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:32:33 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/19 14:09:11 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "structs.h"
#include "utils.h"
#include "cmd_loop.h"

char	*check_absolute_path(char *cmd)
{
	if (access(cmd, X_OK) == -1)
	{
		perror("minishell");
		exit(126);
	}
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	perror_exit();
	return (NULL);
}

int	is_rel_abs_path(char *cmd)
{
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "../", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "/", 1) == 0)
		return (1);
	return (0);
}
