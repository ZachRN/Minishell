/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:14:14 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 10:14:58 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include <stdlib.h>
#include <unistd.h>

int	go_to_other_folder(const char *path, int fd)
{
	int	res;

	res = chdir(path);
	if (res < 0)
	{
		write_str_fd("minishell : cd : ", fd);
		write_str_fd(path, fd);
		write_str_fd(" : No such file or directory\n", fd);
	}
	return (res);
}

//	int len_str = string_len(value) + string_len(name);
//	return (len_str);
int	get_new_len(char *name, char *value)
{
	int	len_str;
	int	len_2;

	len_str = 0;
	len_2 = 0;
	while (name[len_str] != '\0' && name[len_str] != '=')
		len_str++;
	while (value[len_2] != '\0')
		len_2++;
	return (len_str + len_2);
}

///	int len_str = string_len(value) + string_len(name);
char	*join_varname_value_malloc(char *name, char *value)
{
	char	*str;
	int		i;

	i = 0;
	while (*value != '\0' && *value != '=')
		value++;
	str = malloc(sizeof(char) * (get_new_len(name, value) + 1));
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

int	change_pwd_value(t_env_indexes i, t_env_struct *data)
{
	char	buff[1024];

	if (data->new_envp[i.pwd] != NULL)
		free(data->new_envp[i.pwd]);
	if (data->arguments == NULL && i.homevar > 0)
		data->new_envp[i.pwd] = join_varname_value_malloc("PWD=",
				data->envp[i.homevar]);
	else
	{
		if (getcwd(buff, sizeof(buff)) == NULL)
			exit(1);
		data->new_envp[i.pwd] = ft_strjoin("PWD=", buff);
	}
	return (0);
}

int	change_var_value_based_on_indexes(int i_oldpwd, int i_pwd,
											t_env_struct *data)
{
	if (data->new_envp[i_oldpwd] != NULL)
		free(data->new_envp[i_oldpwd]);
	data->new_envp[i_oldpwd] = NULL;
	data->new_envp[i_oldpwd] = join_varname_value_malloc("OLDPWD=",
			data->envp[i_pwd]);
	data->num_var++;
	return (0);
}
