//
//  unset.c
//  minishell_xcd
//
//  Created by Julia Demura on 16/08/2022.
//

#include "unset.h"
#include "builtin_utils.h"
#include <stdio.h>

void	loop_memory(t_env_struct *data)
{
	if (data->new_envp == NULL && data->envp != NULL)
		return ;
	else if (data->envp != NULL)
	{
		free_array_of_str(data->envp);
		data->envp = data->new_envp;
		data->new_envp = NULL;
	}
}

char	**unset_builtin(t_env_struct *data) /// unset works with multiple var names and handle it apperantly one by one
{
	int i;

	i = 0;
	while (data->arguments[i] != NULL)
	{
		if (is_valid_envp_name(data->arguments[i]) == FLS)
		{
			write_not_a_valid_identifier(data->command, data->arguments[i], data->fd_chosen);
			data->last_error = 1; ///error remains even if next argument is valid
		}
		else if (number_var_in_list(data->envp, data->arguments[i]) > 0)
		{
			if (i > 0)
				loop_memory(data);
			data->new_envp = allocate_env_array_without_str(data->envp, data->num_var - 1, data->arguments[i]); //here
			data->num_var--;
		}
		i++;
	}
	return (data->new_envp);
}

