/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:18:00 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 11:20:43 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include "builtin_utils.h"
#include "array_sort.h"
#include <stdlib.h>
#include <stdio.h>

//arguments have parameters https://man7.org/linux/man-pages/man1/export.1p.html

int	new_env_array_size(t_env_struct *data)
{
	int	i;
	int	equal_sign_index;
	int	minus_malloc_size;

	i = 0;
	minus_malloc_size = 0;
	equal_sign_index = 0;
	while (i < data->n_arguments)
	{
		equal_sign_index = find_char_in_str('=', data->arguments[i]);
		if (equal_sign_index == 0
			|| is_valid_envp_name(data->arguments[i]) == FLS)
		{
				minus_malloc_size++;
		}
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
		exit(-1);
}

// here I need to check if var is new, if new, I add in end of arr 
//or rewrite one exsisted
int	alter_envp_new_list(t_env_struct *data, int i)
{
	int	n;

	n = 0;
	if (is_valid_envp_name(data->arguments[i]) == FLS)
	{
		write_not_a_valid_identifier(data->command, data->arguments[i],
			data->fd_chosen);
		data->last_error = 1;
		return (0);
	}
	else if (find_char_in_str('=', data->arguments[i]) > 0)
	{
		n = number_var_in_list(data->envp, data->arguments[i]);
		if (n > 0)
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
	int	i;
	int	sum;

	i = 0;
	sum = new_env_array_size(data);
	if (data->arguments == NULL)
	{
		array_sort_awrite_fd(data->envp, data->num_var, 1);
		return (NULL);
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
