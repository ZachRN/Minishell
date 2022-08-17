//
//  built_in_set.c
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#include "built_in_set.h"

int	if_is_builtin_command(char *str)
{
	char *array_built_in[8];
	int i;

	array_built_in[0] = "echo";
	array_built_in[1] = "cd";
	array_built_in[2] = "pwd";
	array_built_in[3] = "export";
	array_built_in[4] = "export";
	array_built_in[5] = "env";
	array_built_in[6] = "exit";
	array_built_in[7] = NULL;
	i = 0;
	while (i < 7)
	{
		if (compare_str(str, array_built_in[i]) == TRU)
			return (TRU);
		i++;
	}
	return (FLS);
}
