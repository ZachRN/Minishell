//
//  starting_point_after_main.h
//  minishell_xcd
//
//  Created by Julia Demura on 16/08/2022.
//

#ifndef starting_point_after_main_h
#define starting_point_after_main_h

#include <stdio.h>
#include "utils_tests.h"
#include "echo_test.h"
#include "env_test.h"

int	starting_point(void);
char **	enviromental_variable_function(char **envp, char *command, char **arguments);

#endif /* starting_point_after_main_h */
