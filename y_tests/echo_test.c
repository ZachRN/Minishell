//
//  echo_test.c
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#include "echo_test.h"
#include "echo.h"
#include "pwd.h"
#include "env.h"
#include "export.h"
#include "unset.h"
#include "cd.h"
#include "exit.h"

#include <stdio.h>


void	test_echo(void)
{
	char *test_arr[10];
	
	printf("\n-----------TEST1--------------\n");
	test_arr[0] = "try -n in the middle of array";
	test_arr[1] = "-n";
	test_arr[2] = "-n";
	test_arr[3] = "-n";
	test_arr[4] = "test";
	test_arr[5] = NULL;
	int res = echo_builtin(-1, test_arr);///if synopsis == -1 there is non
	
	printf("\n-----------TEST2--------------\n");
	test_arr[0] = "-n";
	test_arr[1] = "-nnnnnn";
	test_arr[2] = "-n";
	test_arr[3] = "nnnnn";
	test_arr[4] = "test";
	test_arr[5] = NULL;
	res = echo_builtin(TRU, test_arr);
	
	printf("\n-----------TEST3--------------\n");
	test_arr[0] = "-n";
	test_arr[1] = "-n";
	test_arr[2] = "-n";
	test_arr[3] = "new";
	test_arr[4] = "test";
	test_arr[5] = NULL;
	res = echo_builtin(TRU, test_arr);
	
}
