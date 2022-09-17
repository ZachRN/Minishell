//
//  cd.c
//  minishell_xcd
//
//  Created by Julia Demura on 24/08/2022.
//

#include "cd.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

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

char	*join_varname_value_malloc(char *name, char *value)
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

int change_pwd_value(t_env_indexes i, t_env_struct *data) //const char *cd_arg
{
	char buff[1024];
	
	if (data->new_envp[i.pwd] != NULL)
		free(data->new_envp[i.pwd]);
	if (data->arguments == NULL && i.homevar > 0) //cd_arg == NULL
		data->new_envp[i.pwd] = join_varname_value_malloc("PWD=", data->envp[i.homevar]);
	else
	{
		if (getcwd(buff, sizeof(buff)) == NULL)
			exit(1);// not sure its correct
		data->new_envp[i.pwd] = ft_strjoin("PWD=", buff);
	}
		
	return (0);
}

int change_var_value_based_on_indexes(int i_oldpwd, int i_pwd, t_env_struct *data)
{
	if (data->new_envp[i_oldpwd] != NULL)
		free(data->new_envp[i_oldpwd]);
	data->new_envp[i_oldpwd] = NULL;
	data->new_envp[i_oldpwd] = join_varname_value_malloc("OLDPWD=", data->envp[i_pwd]);
	data->num_var++;
	return (0);
}

char	**handle_enviromntl(t_env_indexes index, t_env_struct *data)
{
	int j;

	j = 0;
	while (data->envp[j] != NULL)
	{
		if (j == index.oldpwd)
			change_var_value_based_on_indexes(j, index.pwd, data);
		else if (j == index.pwd)
			change_pwd_value(index, data); //cd_arg
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
	data->new_envp[data->num_var] = NULL;
	return (data->new_envp);
}

char	*pick_argument_for_cd(char **arguments, const char *home_var)
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

char	**change_enviromental_variable_after_cd(t_env_indexes i, t_env_struct *data)
{
	int len;
	
	i.pwd = number_var_in_list(data->envp, "PWD=") - 1;
	i.oldpwd = number_var_in_list(data->envp, "OLDPWD=") - 1;
	len = data->num_var + 1;
	if (i.oldpwd < 0)
		len++;
	data->new_envp = malloc(sizeof(char *) * len); ///create new_envp, cope from data->envp if envp NULL, which I need to test
	if (data->new_envp == NULL)
		exit(1);
	data->new_envp = fill_nulls(0, data->num_var, data->new_envp);
	handle_enviromntl(i, data);
	return (data->new_envp);
}

char	**cd_builtin(t_env_struct *data)
{
	t_env_indexes index;
	char *cd_arg;

	index.homevar = number_var_in_list(data->envp, "HOME=") - 1;
	if (data->arguments == NULL && index.homevar < 0) ///bone CD command use HOME env var to go there but if unset HOME and not give any arg to cd there is no path
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
