//
//  cd.c
//  minishell_xcd
//
//  Created by Julia Demura on 24/08/2022.
//

#include "cd.h"
#include <stdlib.h>
#include <unistd.h>

int go_to_other_folder(const char *path, int fd)
{
	int res;

	res = chdir(path);
	if (res < 0)
	{
		write_str_fd("minishell : cd : ", fd);
		write_str_fd(path, fd);
		write_str_fd(" : No such file or directory\n", fd);
	}
	return (res);
}

int	get_new_len(char *name, char *value)
{
	int len_str;
	int len_2;

	len_str = 0;
	len_2 = 0;
	while (name[len_str] != '\0' && name[len_str] != '=')
		len_str++;
	while (value[len_2] != '\0')
		len_2++;
//	int len_str = string_len(value) + string_len(name);
//	return (len_str);
	
	return (len_str + len_2);
}

char *join_varname_value_malloc(char *name, char *value)
{
	char *str;
	int i;

	i = 0;
	while (*value != '\0' && *value != '=')
		value++;
	str = malloc(sizeof(char) * (get_new_len(name, value) + 1)); ///	int len_str = string_len(value) + string_len(name);
	if (str == NULL)
		exit(1);
	while (*name != '=')
	{
		str[i] = *name;
		i++;
		name++;
	}
	while (*value != '\0')
	{
		str[i] = *value;
		i++;
		value++;
	}
	str[i] = '\0';
	return (str);
}

int change_pwd_value(t_env_struct *data, int i_homevar, int i_pwd)
{
	if (data->new_envp[i_pwd] != NULL)
		free(data->new_envp[i_pwd]);
	if (data->arguments != NULL && data->arguments[0] == NULL && i_homevar > 0)
		data->new_envp[i_pwd] = join_varname_value_malloc("PWD=", data->envp[i_homevar]);
	else
		data->new_envp[i_pwd] = ft_strjoin("PWD=", data->arguments[0]);
	return (0);
}

int change_var_value_based_on_indexes(t_env_struct *data, int i_oldpwd, int i_pwd)
{
	if (data->new_envp[i_oldpwd] != NULL)
		free(data->new_envp[i_oldpwd]);
	data->new_envp[i_oldpwd] = NULL;
	data->new_envp[i_oldpwd] = join_varname_value_malloc("OLDPWD=", data->envp[i_pwd]);
	data->num_var++;
	return (0);
}

char **	handle_enviromntl(t_env_struct *data, int i_homevar, int i_pwd, int i_oldpwd)
{
	int i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (i == i_oldpwd)
			change_var_value_based_on_indexes(data, i, i_pwd);
		else if (i == i_pwd)
			change_pwd_value(data, i_homevar, i);
		else
		{
			data->new_envp[i] = ft_strdup(data->envp[i]);
			if (data->new_envp[i] == NULL)
				exit(1);
		}
		i++;
	}
	if (i_oldpwd < 0)
	{
		change_var_value_based_on_indexes(data, i, i_pwd);
		i++;
	}
	data->new_envp[data->num_var] = NULL;
	return (data->new_envp);
}

char *pick_argument_for_cd(char **arguments, const char *home_var)
{
	char *path;

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

char **change_enviromental_variable_after_cd(int i_homevar, const char *cd_arg, t_env_struct *data)
{
	int i_pwd;
	int i_oldpwd;
	int len;
	
	i_pwd = number_var_in_list(data->envp, "PWD=") - 1;
	i_oldpwd = number_var_in_list(data->envp, "OLDPWD=") - 1;
	len = data->num_var + 1;
	if (i_oldpwd < 0)
		len++;
	data->new_envp = malloc(sizeof(char *) * len); ///create new_envp, cope from data->envp if envp NULL, which I need to test
	if (data->new_envp == NULL)
		exit(1);
	data->new_envp = fill_nulls(0, data->num_var, data->new_envp);
	handle_enviromntl(data, i_homevar, i_pwd, i_oldpwd);
	return (data->new_envp);
}

char**	cd_builtin(t_env_struct *data)
{
	int i_homevar;
	const char *cd_arg;

	i_homevar = number_var_in_list(data->envp, "HOME=") - 1;
	if (data->arguments == NULL && i_homevar < 0) ///bone CD command use HOME env var to go there but if unset HOME and not give any arg to cd there is no path
	{
		write_str_fd("minishell: cd: HOME not set", data->fd_chosen);
		return (NULL);
	}
	cd_arg = pick_argument_for_cd(data->arguments, data->envp[i_homevar]);
	if (go_to_other_folder(cd_arg, data->fd_chosen) >= 0)
	{
		data->new_envp = change_enviromental_variable_after_cd(i_homevar, cd_arg, data);
		return (data->new_envp);
	}
	return (NULL);
}
//TODO if argument == ".." need to go back

//error messages
//bash: cd: Docume/: No such file or directory
