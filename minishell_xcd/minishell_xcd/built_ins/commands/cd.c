//
//  cd.c
//  minishell_xcd
//
//  Created by Julia Demura on 24/08/2022.
//

#include "cd.h"

int go_to_other_folder(char *argument, char *home_var)
{
	int res;
	const char *path;

	if (argument != NULL)
		path = (const char *)argument;
	else
	{
		if (home_var != NULL)
		{
			while (*home_var != '=')
				home_var++;
			home_var++;
			path = (const char *)home_var;
		}
	}
	res = chdir(path); //dont know how to test
	return (res);
}

//#include<stdio.h>
//#include<unistd.h>
//int main()
//{
//  char cwd[256];
//
//  if (chdir("Your desired path") != 0)
//	perror("chdir() error()");
//  else {
//	if (getcwd(cwd, sizeof(cwd)) == NULL)
//	  perror("getcwd() error");
//	else
//	  printf("current working directory is: %s\n", cwd);
//  }
//} WAY vto test, example



int if_array_need_be_longer(t_env_data *data, int i_oldpwd) ///	old_pwd was nulled by me in shift_array_delete_var(envp, "OLDPWD=") or never existed , I need to make space for it in new_envp array
{
	if (i_oldpwd < 0)
	{
		data->new_envp = malloc(sizeof(char *) * (find_arr_len(data->envp) + 2));
		if (data->new_envp == NULL)
			return (ERR);
		return (TRU);
	}
	return (FLS);
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
	return (len_str + len_2);
}

char *join_varname_value_malloc(char *name, char *value)
{
	char *str;
	int i;

	i = 0;
	while (*value != '\0' && *value != '=')
		value++;
//	int len_str = string_len(value) + string_len(name);
//	str = malloc(sizeof(char) * (len_str + 1));
	str = malloc(sizeof(char) * (get_new_len(name, value) + 1));
	if (str == NULL)
		return (NULL);
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

int check_home_var(t_env_data *data, int i_homevar, int i_pwd, int i_oldpwd)
{
	if (data->arguments[0] == NULL && i_homevar > 0)
	{
		data->envp[i_oldpwd] = join_varname_value_malloc("OLDPWD=", data->envp[i_pwd]);
		if (data->envp[i_oldpwd] == NULL)
			return (ERR); /// malloc err
		data->envp[i_pwd] = join_varname_value_malloc("PWD=", data->envp[i_homevar]);
		if (data->envp[i_pwd] == NULL)
			return (ERR); /// malloc err
		return (TRU); /// home and 0 arg worked
	}
	return(0);
}


int handle_pwd_with_without_arguments(t_env_data *data, int i_homevar, int i_pwd)
{
	if (data->arguments[0] == NULL && i_homevar > 0)
	{
		data->new_envp[i_pwd] = join_varname_value_malloc("PWD=", data->envp[i_homevar]);
		if (data->new_envp[i_pwd] == NULL)
			return (ERR); /// malloc err
	}
	else
	{
		data->new_envp[i_pwd] = join_varname_value_malloc("PWD=", data->arguments[0]);
		if (data->new_envp[i_pwd] == NULL)
			return (ERR);
	}
	return (0);
}

int handle_oldpwd_(t_env_data *data, int i_oldpwd, int i_pwd)
{
	data->new_envp[i_oldpwd] = join_varname_value_malloc("OLDPWD=", data->envp[i_pwd]);
	if (data->new_envp[i_oldpwd] == NULL)
		return (ERR); /// malloc err
	data->num_var++;
	return (0);
}

int no_oldpwd_continue_handle_envp(int i_oldpwd, int i, int i_pwd, t_env_data *data)
{
	if (i_oldpwd < 0)
	{
		if (handle_oldpwd_(data, i, i_pwd) == ERR)
			return (ERR);
	}
	data->new_envp[i + 1] = NULL;
	return (0);
}


int	handle_enviromntl(t_env_data *data, int i_homevar, int i_pwd, int i_oldpwd)
{
	int i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (i == i_oldpwd)
		{
			if (handle_oldpwd_(data, i_oldpwd, i_pwd) == ERR)
				return (ERR);
		}
		else if (i == i_pwd)
		{
			if (handle_pwd_with_without_arguments(data, i_homevar, i_pwd) == ERR)
				return (ERR);
		}
		else
			data->new_envp[i] = data->envp[i];
		i++;
	}
	if (no_oldpwd_continue_handle_envp(i_oldpwd, i, i_pwd, data) == ERR)
			return (ERR);
	return (0);
}


char**	cd_builtin(t_env_data *data)
{
	int i_homevar;
	int i_pwd;
	int i_oldpwd;

	i_pwd = number_var_in_list(data->envp, "PWD=") - 1;
	i_oldpwd = number_var_in_list(data->envp, "OLDPWD=") - 1;
	i_homevar = number_var_in_list(data->envp, "HOME=") - 1;
	if (if_array_need_be_longer(data, i_oldpwd) == ERR)
		return (NULL); /// malloc error

	if (handle_enviromntl(data, i_homevar, i_pwd, i_oldpwd) == ERR)
		return (NULL);

	if (go_to_other_folder(data->arguments[0], data->new_envp[i_homevar]) == -1)
		return (NULL); ///function made an error and will give errno
	return (data->new_envp);
}



///I always leave PWD and OLDPWD malloced
// need to check if they are already malloced and if I need to free before malloc

//error messages \
bash: cd: Docume/: No such file or directory \
