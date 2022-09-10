//
//  export.c
//  minishell_xcd
//
//  Created by Julia Demura on 16/08/2022.
//

#include "export.h"

//arguments have parameters https://man7.org/linux/man-pages/man1/export.1p.html

int new_env_array_size(t_env_struct *data)
{
	int i;
	int equal_sign_index;
	int minus_malloc_size;

	i = 0;
	minus_malloc_size = 0;
	equal_sign_index = 0;
	while (i < data->n_arguments)
	{
		equal_sign_index = find_char_in_str('=', data->arguments[i]);
		if (equal_sign_index == 0 || is_valid_envp_name(data->arguments[i]) == FLS)
			minus_malloc_size++; ///so I know no = sign in variable and it wont make it in list
		if (number_var_in_list(data->envp, data->arguments[i]) > 0)
			minus_malloc_size++;
		i++;
	}
	return (data->n_arguments - minus_malloc_size + data->num_var);
}

void	copy_str_for_data(t_env_struct *data, int i_dst, int i_src)
{
	if (data->new_envp[i_dst] != NULL)
		free(data->new_envp[i_dst]);
	data->new_envp[i_dst] = ft_strdup(data->arguments[i_src]);
	if (data->new_envp[i_dst] == NULL)
		exit (-1);
}

int	alter_envp_new_list(t_env_struct *data, int i) /// here I need to check if var is new, if new, I add in end of arr or rewrite one exsisted
{
	int n;

	n = 0;
	if (find_char_in_str('=', data->arguments[i]) > 0)
	{
		n = number_var_in_list(data->envp, data->arguments[i]); /// not index but number
///		if (is_number(data->arguments[i][0]) == TRU || data->arguments[i][0] == '?')
///		{
///			printf("\n Minishell : %s : '%s' : not a valid identifier", data->command, data->arguments[i]);
///			return (0);
///		}
		if (is_valid_envp_name(data->arguments[i]) == FLS)
		{
			printf("\n Minishell : %s : '%s' : not a valid identifier", data->command, data->arguments[i]);
			return (0);
		}
		if (n > 0) /// if var already exists I need to rewrite it by index
			copy_str_for_data(data, n - 1, i);
		else
		{
			copy_str_for_data(data, data->num_var, i);
			data->num_var++;
		}
	}
	return (0);
}

char	**export_builtin(t_env_struct *data)
{
	int i;
	int sum;

	i = 0;
	sum = new_env_array_size(data);
	if (data->arguments == NULL)
	{
		array_sort_awrite_fd(data->envp, data->num_var, 1); //NEED TO TEST
		data->new_envp = allocate_env_array_without_str(data->envp, sum, NULL);
		return (data->new_envp);
	}
	data->new_envp = allocate_env_array_without_str(data->envp, sum, NULL);
	if (data->new_envp == NULL)
		exit(1);
	while (i < data->n_arguments)
	{
		alter_envp_new_list(data, i);
		i++;
	}
	return (data->new_envp);
}
