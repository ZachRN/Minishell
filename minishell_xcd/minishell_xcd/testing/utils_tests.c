//
//  utils_tests.c
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#include "utils_tests.h"



int	test_builtin_utils(void)
{
	char *name;
	char *argument;
	char c;
	
	name = "HEY=hehehe";
	argument = "HEY=lalala";
	c = '=';
	assert(compare_str_till_char(name, argument, c) == TRU);
	
	name = "HE=hehehe";
	argument = "HEY=lalala";
	c = 'E';
	assert(compare_str_till_char(name, argument, c) == TRU);
	
	name = "HE=hehehe";
	argument = "HEY=lalala";
	c = '=';
	assert(compare_str_till_char(name, argument, c) == FLS);
	
	name = "HE145=lalala";
	argument = "HE451=lalala";
	c = 'l';
	assert(compare_str_till_char(name, argument, c) == FLS);
	
	name = "VAR=one_value";
	argument = "VARIABLE";
	c = '=';
	assert(compare_str_till_char(name, argument, c) == FLS);
	
	name = "";
	argument = "VARIABLE=";
	c = '=';
	assert(compare_str_till_char(name, argument, c) == FLS);
	
	name = NULL;
	argument = "VARIABLE=";
	c = '=';
	assert(compare_str_till_char(name, argument, c) == FLS);
	
	name = "VARIABLE";
	argument = "VARIABLE";
	c = '=';
	assert(compare_str_till_char(name, argument, c) == FLS);
	
	name = "VARIABLE=lalalala";
	argument = "VARIABLE";
	c = '=';
	assert(compare_str_till_char(name, argument, c) == TRU);
	

	
	
	return 0;
}
