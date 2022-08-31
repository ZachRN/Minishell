//
//  starting_point_after_main.c
//  minishell_xcd
//
//  Created by Julia Demura on 16/08/2022.
//

#include "starting_point_after_main.h"

char **enviromental_variable_function(char **envp, char *command, char **arguments)
{
	t_env_data data;

	data.command = command;
	data.arguments = arguments;
	data.n_arguments = find_arr_len(arguments);

	data.envp = allocate_env_array_without_str(envp, find_arr_len(envp), "OLDPWD"); //malloced envp
	data.envp = built_in_commands(&data); // malloced new_envp in export, free envp, reassighn envp
	// need to manage memory at this point as I am rewriting data.envp and leaking memory.  need to free in in a function before.
	return (data.envp);
}

int	starting_point(void)
{
	// insert code here...
		printf("				start\n\n****************************************\n\n");

		test_builtin_utils();
	//	test_echo();
	//	test_env_series(envp);
	test_change_variable();
	
	return (0);
}
