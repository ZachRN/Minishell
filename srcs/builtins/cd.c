/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:10:51 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 11:15:24 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

char	**handle_enviromntl(t_env_indexes index, t_env_struct *data)
{
	int	j;

	j = 0;
	while (data->envp[j] != NULL)
	{
		if (j == index.oldpwd)
			change_var_value_based_on_indexes(j, index.pwd, data);
		else if (j == index.pwd)
			change_pwd_value(index, data);
		else
		{
			data->new_envp[j] = ft_strdup(data->envp[j]);
			if (data->new_envp[j] == NULL)
				exit(1);
		}
		j++;
	}
	if (index.oldpwd < 0)
	{
		change_var_value_based_on_indexes(j, index.pwd, data);
		j++;
	}
	data->new_envp[data->num_var] = NULL; //fsanitize complaint
	return (data->new_envp);
}

char	*pick_argument_for_cd(char **arguments, const char *home_var)
{
	char	*path;

	path = NULL;
	if (arguments != NULL)
		path = ft_strdup(arguments[0]);
	else
	{
		if (home_var != NULL)
		{
			while (*home_var != '=')
				home_var++;
			home_var++;
			path = ft_strdup(home_var);
		}
	}
	return (path);
}

char	**change_enviromental_variable_after_cd(t_env_indexes i,
												t_env_struct *data)
{
	int	len;

	i.pwd = number_var_in_list(data->envp, "PWD=") - 1;
	i.oldpwd = number_var_in_list(data->envp, "OLDPWD=") - 1;
	len = data->num_var + 1;
	if (i.oldpwd < 0)
		len++;
	data->new_envp = malloc(sizeof(char *) * (len + 1));
	if (data->new_envp == NULL)
		exit(1);
	data->new_envp = fill_nulls(0, data->num_var, data->new_envp);
	handle_enviromntl(i, data);
	return (data->new_envp);
}

//bone CD command use HOME env var to go there but if unset HOME
//and not give any arg to cd there is no path
char	**cd_builtin(t_env_struct *data)
{
	t_env_indexes	index;
	char			*cd_arg;

	index.homevar = number_var_in_list(data->envp, "HOME=") - 1;
	if (data->arguments == NULL && index.homevar < 0)
	{
		write_str_fd("minishell: cd: HOME not set", data->fd_chosen);
		return (NULL);
	}
	cd_arg = pick_argument_for_cd(data->arguments, data->envp[index.homevar]);
	if (go_to_other_folder(cd_arg, data->fd_chosen) >= 0)
	{
		data->new_envp = change_enviromental_variable_after_cd(index, data);
		free(cd_arg);
		return (data->new_envp);
	}
	free(cd_arg);
	return (NULL);
}
