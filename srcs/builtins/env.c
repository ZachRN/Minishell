//
//  env.c
//  minishell_xcd
//
//  Created by Julia Demura on 12/08/2022.
//

#include "env.h"
#include "builtin_utils.h"

//https://www.geeksforgeeks.org/c-program-print-environment-variables/
//char * envp[]



int	env_builtin(char **env_arg, int fd) /// env with no options or arguments
{
	int i;

	i = 0;
	while (env_arg[i] != NULL)
	{
		write_str_fd(env_arg[i], fd);
		i++;
	}
	return (0);
}


