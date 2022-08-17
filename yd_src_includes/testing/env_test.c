//
//  env_test.c
//  minishell_xcd
//
//  Created by Julia Demura on 12/08/2022.
//

#include "env_test.h"
#include <stdlib.h>

void test_env_series(char **env)
{
	env_builtin(env);
}


int	test_change_variable(char **env)
{
	char *name;
	
	name = "TEST_VAR";
	
	return 0;
}
