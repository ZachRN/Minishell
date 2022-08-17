//
//  export.c
//  minishell_xcd
//
//  Created by Julia Demura on 16/08/2022.
//

#include "export.h"

//export always add at the bottom - or not lol
//export works with multiple arguments unset as well
//arguments have parameters https://man7.org/linux/man-pages/man1/export.1p.html

///	bash-3.2$ export 1tell=jek
///	bash: export: `1tell=jek': not a valid identifier

/// there can be a few agduments VAR=value and they all will be added to a list with 1 export command.


char**	export_builtin(char **env_arg, char **arguments)
{
	int number_of_new_var;
	int len_of_old_arr;
	char** updated_envp;
	int i;

	number_of_new_var = find_arr_len(arguments);
	len_of_old_arr = find_arr_len(env_arg);
	i = 0;
	updated_envp = array_realloc(env_arg, number_of_new_var, len_of_old_arr);
	while (i < number_of_new_var)
	{
		updated_envp[len_of_old_arr] = arguments[i];
		i++;
		len_of_old_arr++;
	}
	return (updated_envp);
}
