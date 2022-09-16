//
//  built_in_set.c
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#include "built_in_set.h"
#include "commands.h"
#include <stdlib.h>

#include <stdio.h>

int	initiate_data_struct(char *command, t_env_struct *data)
{
	char *array_built_in[8];

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

char **built_in_commands(t_env_struct *data)
{
	initiate_data_struct(data->command, data);
	if (data->comm_n == ECHO)
		echo_builtin(data->arguments, data->fd_chosen);
	else if(data->comm_n == PWD)
		pwd_builtin(data->fd_chosen);
	else if (data->comm_n == EXPORT)
		export_builtin(data);
	else if (data->comm_n == ENV)
		env_builtin(data->envp, data->fd_chosen);
	else if (data->comm_n == UNSET)
		unset_builtin(data);
	else if (data->comm_n == CD)
		cd_builtin(data);
	else if (data->comm_n == EXIT)
		exit_builtin(data, data->last_error);
	free_array_of_str(data->envp);
	return (data->new_envp);
}

/// make error message - export and unset, same format described in export c file



int	pick_fd_for_builtin(t_fd fd)/// decide which fd has priority? how to pick one
{
	if (fd.outfile >= 0)
		return (fd.outfile);
	else if (fd.pipe[1] >= 0)
		return (fd.pipe[1]);
	else
		return (STDOUT_FILENO);
}

char **enviromental_variable_function(char **envp, char *command, char **arguments, t_fd fd)
{
	t_env_struct data;
	int len;

	data.command = command;
	if (arguments[1] == NULL)
		data.arguments = NULL;
	else
		data.arguments = arguments;
	data.n_arguments = find_arr_len(arguments);
	data.fd_chosen = pick_fd_for_builtin(fd);
	data.last_error = 0;

	len = find_arr_len(envp);
	data.envp = allocate_env_array_without_str(envp, len, "OLDPWD"); //malloced envp
	data.envp = built_in_commands(&data); // malloced new_envp in export, free envp, reassighn envp
	// need to manage memory at this point as I am rewriting data.envp and leaking memory.  need to free in in a function before.
	return (data.envp);
}
