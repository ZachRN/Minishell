/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:08:00 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 10:09:46 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_set.h"
#include "commands.h"
#include <stdlib.h>

int	initiate_data_struct(char *command, t_env_struct *data)
{
	char	*array_built_in[8];

	array_built_in[0] = "echo";
	array_built_in[1] = "cd";
	array_built_in[2] = "pwd";
	array_built_in[3] = "export";
	array_built_in[4] = "env";
	array_built_in[5] = "unset";
	array_built_in[6] = "exit";
	array_built_in[7] = NULL;
	data->comm_n = 0;
	while (data->comm_n < 7)
	{
		if (compare_str(array_built_in[data->comm_n], command) == TRU)
			break ;
		data->comm_n++;
	}
	data->num_var = find_arr_len(data->envp);
	data->envvar_repeat = 0;
	data->new_envp = NULL;
	return (0);
}

char	**built_in_commands(t_env_struct *data, int pid)
{
	initiate_data_struct(data->command, data);
	if (data->comm_n == ECHO)
		echo_builtin(data->arguments, data->fd_chosen);
	else if (data->comm_n == PWD)
		data->last_error = pwd_builtin(data->fd_chosen);
	else if (data->comm_n == ENV)
		env_builtin(data->envp, data->fd_chosen);
	else if (data->comm_n == EXIT)
		exit_builtin(data, pid);
	else if (data->comm_n == UNSET)
		unset_builtin(data);
	else if (data->comm_n == EXPORT)
		export_builtin(data);
	else if (data->comm_n == CD)
		cd_builtin(data);
	free_array_of_str(data->envp);
	if (data->last_error != 0)
		return (NULL);
	return (data->new_envp);
}

int	manage_arg_and_fd_for_data(char **arguments, int to_write,
											t_env_struct *data)
{
	data->command = arguments[0];
	if (arguments[1] == NULL)
		data->arguments = NULL;
	else
	{
		arguments++;
		data->arguments = arguments;
	}
	data->n_arguments = find_arr_len(data->arguments);
	data->fd_chosen = STDOUT_FILENO; //IF i am correct
	return (to_write);
}

char	**enviromental_variable_function(t_exec *exec, char **arguments,
													int to_write)
{
	t_env_struct	data;
	int				len;

	data.fd_chosen = manage_arg_and_fd_for_data(arguments, to_write, &data);
	data.last_error = 0;
	data.prev_builtin_err = exec->builtin_error;
	len = find_arr_len(exec->envp);
	data.envp = allocate_env_array_without_str(exec->envp, len, NULL);
	data.envp = built_in_commands(&data, exec->params[exec->index].child_pid);
	if (exec->last_error != 1)
		exec->last_error = data.last_error;
	return (data.envp);
}
