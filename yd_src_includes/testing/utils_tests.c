//
//  utils_tests.c
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#include "utils_tests.h"


int	test_build_checker(void)
{
	char *test_arr[10];
	int i;

	test_arr[0] = "echono";
	test_arr[1] = "nono";
	test_arr[2] = "";
	test_arr[3] = NULL;
	test_arr[4] = "exitexit";
	test_arr[5] = "penv";
	test_arr[6] = "exite";
	test_arr[7] = "012";
	test_arr[8] = "pwwd";
	
	i = 0;
	
	while (i < 8)
	{
		assert(if_is_builtin_command(test_arr[i]) == FLS);
		i++;
	}
	
	test_arr[0] = "echo";
	test_arr[1] = "cd";
	test_arr[2] = "pwd";
	test_arr[3] = "export";
	test_arr[4] = "export";
	test_arr[5] = "env";
	test_arr[6] = "exit";
	
	i = 0;
	
	while (i < 7)
	{
		assert(if_is_builtin_command(test_arr[i]) == TRU);
		i++;
	}
	
	return 0;
}
