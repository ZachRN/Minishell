//
//  env.c
//  minishell_xcd
//
//  Created by Julia Demura on 12/08/2022.
//

#include "env.h"

//https://www.geeksforgeeks.org/c-program-print-environment-variables/
//char * envp[]



int	env_builtin(char **env_arg) /// env with no options or arguments
{
	int i;

	i = 0;
	while (env_arg[i] != NULL)
	{
		printf("%s\n", env_arg[i]);
		i++;
	}
	return (0);
}


