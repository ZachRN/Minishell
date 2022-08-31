//
//  utils_tests.c
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#include "utils_tests.h"



int	test_builtin_utils(void)
{
	char *s1;
	char *s2;
	char c;
	
	s1 = "HEY=hehehe";
	s2 = "HEY=lalala";
	c = '=';
	assert(compare_str_till_char(s1, s2, c) == TRU);
	
	s1 = "HE=hehehe";
	s2 = "HEY=lalala";
	c = 'E';
	assert(compare_str_till_char(s1, s2, c) == TRU);
	
	s1 = "HE=hehehe";
	s2 = "HEY=lalala";
	c = '=';
	assert(compare_str_till_char(s1, s2, c) == FLS);
	
	s1 = "HE145=lalala";
	s2 = "HE451=lalala";
	c = 'l';
	assert(compare_str_till_char(s1, s2, c) == FLS);
	
	s1 = "VAR=one_value";
	s2 = "VARIABLE";
	c = '=';
	assert(compare_str_till_char(s1, s2, c) == FLS);
	
	s1 = "";
	s2 = "VARIABLE=";
	c = '=';
	assert(compare_str_till_char(s1, s2, c) == FLS);
	
	s1 = NULL;
	s2 = "VARIABLE=";
	c = '=';
	assert(compare_str_till_char(s1, s2, c) == FLS);
	
	s1 = "VARIABLE";
	s2 = "VARIABLE";
	c = '=';
	assert(compare_str_till_char(s1, s2, c) == FLS);
	
	
	return 0;
}
