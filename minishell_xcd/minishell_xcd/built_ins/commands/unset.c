//
//  unset.c
//  minishell_xcd
//
//  Created by Julia Demura on 16/08/2022.
//

#include "unset.h"

//unsetting bullshit is giving next bash line, same with no arg

// command ends with newline, doest matter if env exists
///if env in argument does not exists, bash does nothing - newline
/// if invilid identifier, unset still unsets all that needed but then write error message

// BUT unset 1bullshit ->>>> bash: unset: `1bullshit': not a valid identifier
// bash: unset: `^bullshit': not a valid identifier "^" reacts same as number at the front of var
// bash: unset: `TEST=1': not a valid identifier

void	loop_memory(t_env_data *data)
{
	if (data->new_envp == NULL && data->envp != NULL)
		return ;
	else if (data->envp != NULL)
	{
		free_array_of_str(data->envp);
		data->envp = data->new_envp;
		data->new_envp = NULL; ///	do not free 
	}
	
}


char	**unset_builtin(t_env_data *data) /// unset works with multiple var names and handle it apperantly one by one
{
	int i;

	i = 0;
	while (data->arguments[i] != NULL)
	{
		if (is_valid_envp_name(data->arguments[i]) == FLS)
			printf("\n Minishell : %s : '%s' : not a valid identifier", data->command, data->arguments[i]);
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

