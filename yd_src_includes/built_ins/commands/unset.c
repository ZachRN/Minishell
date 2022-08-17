//
//  unset.c
//  minishell_xcd
//
//  Created by Julia Demura on 16/08/2022.
//

#include "unset.h"

//unsetting bullshit is giving next bash line, same with no arg

char**	unset_builtin(char **env_arg, char **arguments) /// unset works with multiple var names and handle it apperantly one by one
{
	int number_of_new_var;
	int len_of_old_arr;
	char** updated_envp;
	int i;

	number_of_new_var = find_arr_len(arguments);
	len_of_old_arr = find_arr_len(env_arg);
	i = 0;
///	char	**array_realloc(char **array, int len_of_old_arr, int new_len)
	updated_envp = array_realloc(env_arg, len_of_old_arr, number_of_new_var + len_of_old_arr);
	while (i < number_of_new_var)
	{
		updated_envp[len_of_old_arr] = arguments[i];
		i++;
		len_of_old_arr++;
	}
	return (updated_envp);
}
