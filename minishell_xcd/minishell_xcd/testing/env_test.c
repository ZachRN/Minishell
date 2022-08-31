//
//  env_test.c
//  minishell_xcd
//
//  Created by Julia Demura on 12/08/2022.
//

#include "env_test.h"
#include <stdlib.h>
#include "starting_point_after_main.h"
#include "string.h"


void test_env_series(char **env)
{
	env_builtin(env);
}

///input: export EXISTING_VAR=value
///input: export NEW_VAR=value

//STILL NEED:
///input: export 1_ERR=error, followed with error message


void	incorrect_inp1(char *command)
{
	char *envp[10];
	char *arguments[4];
	char **new_envp;
	
	printf("\n-----------TEST : incorrect input--------------\n");
	envp[0] = "HOME=/Users/yuliia";
	envp[1] = "PWD=/Users/yuliia/Desktop/minishell";
	envp[2] = "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:bin";
	envp[3] = "SHLVL=1";
	envp[4] = "CLASSIC_VAR=classic_value";
	envp[5] = "OLDPWD=random_somth";
	envp[6] = NULL;

	if (strcmp(command, "export") == 0)
	{
		arguments[0] = "EMPTY_VAR";
		arguments[1] = "2WRONG2=sting_is_longer";
		arguments[2] = "CORRECT_TO_CHECK=string_is_shorter";
		arguments[3] = NULL;
	}
	else if (strcmp(command, "unset") == 0)
	{
		arguments[0] = "2WRONG";
		arguments[1] = "?WRONG";
		arguments[2] = "CLASSIC_VAR";
		arguments[3] = NULL;
	}
	
	new_envp = enviromental_variable_function(envp, command, arguments);
	if (strcmp(command, "export") == 0)
	{
		assert(strcmp(new_envp[0], "HOME=/Users/yuliia") == 0);
		assert(strcmp(new_envp[1], "PWD=/Users/yuliia/Desktop/minishell") == 0);
		assert(strcmp(new_envp[2], "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:bin") == 0);
		assert(strcmp(new_envp[3], "SHLVL=1") == 0);
		assert(strcmp(new_envp[4], "CLASSIC_VAR=classic_value") == 0);
		assert(strcmp(new_envp[5], "CORRECT_TO_CHECK=string_is_shorter") == 0);
		if (new_envp[6] != NULL)
			printf("nope, there is smth instead of NULL:\n%s\n", new_envp[6]);
	}
	if (strcmp(command, "unset") == 0)
	{
		assert(strcmp(new_envp[0], "HOME=/Users/yuliia") == 0);
		assert(strcmp(new_envp[1], "PWD=/Users/yuliia/Desktop/minishell") == 0);
		assert(strcmp(new_envp[2], "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:bin") == 0);
		assert(strcmp(new_envp[3], "SHLVL=1") == 0);
		if (new_envp[4] != NULL)
			printf("nope, there is smth instead of NULL:\n%s\n", new_envp[4]);
	}
	printf("\n");
}

void	correct_input(char *command)
{
	char *envp[10];
	char *arguments[4];
	char **new_envp;
	
	printf("\n-----------TEST : correct input--------------\n");
	envp[0] = "HOME=/Users/yuliia";
	envp[1] = "OLDPWD=/Users/yuliia/Desktop/minishell";
	envp[2] = "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:";
	envp[3] = "SHLVL=1";
	envp[4] = "PWD=julia/my_lolder_with_dream";
	envp[5] = "CLASSIC_VAR=classic_value";
	envp[6] = NULL;

	if (strcmp(command, "export") == 0)
	{
		arguments[0] = "CLASSIC_VAR=classic_value_updated_string_same";
		arguments[1] = "CLASSIC_VAR2=sting_is_longer";
		arguments[2] = "CLASSIC_=string_is_shorter";
		arguments[3] = NULL;
	}
	else if (strcmp(command, "unset") == 0)
	{
		arguments[0] = "CLASSIC_VAR";
		arguments[1] = "CLASSIC_VAR2";
		arguments[2] = NULL;
	}
	
	new_envp = enviromental_variable_function(envp, command, arguments); //test it
	
	
	if (strcmp(command, "export") == 0)
	{
		assert(strcmp(new_envp[0], "HOME=/Users/yuliia") == 0);
		assert(strcmp(new_envp[1], "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:") == 0);
		assert(strcmp(new_envp[2], "SHLVL=1") == 0);
		assert(strcmp(new_envp[3], "PWD=julia/my_lolder_with_dream") == 0);
		//printf("\n%s\n", new_envp[4]);
		assert(strcmp(new_envp[4], "CLASSIC_VAR=classic_value_updated_string_same") == 0);
		assert(strcmp(new_envp[5], "CLASSIC_VAR2=sting_is_longer") == 0);
		assert(strcmp(new_envp[6], "CLASSIC_=string_is_shorter") == 0);
		if (new_envp[7] != NULL)
			printf("nope, there is smth instead of NULL:\n%s\n", new_envp[7]);
	}
	else if (strcmp(command, "unset") == 0)
	{
		assert(strcmp(new_envp[0], "HOME=/Users/yuliia") == 0);
		assert(strcmp(new_envp[1], "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:") == 0);
		assert(strcmp(new_envp[2], "SHLVL=1") == 0);
		assert(strcmp(new_envp[3], "PWD=julia/my_lolder_with_dream") == 0);
		if (new_envp[4] != NULL)
			printf("nope, there is smth instead of NULL:\n%s\n", new_envp[4]);
	}
	printf("\n");
}

void	test_cd(void)
{
	char *envp[10];
	char *arguments[4];
	char **new_envp;
	
	printf("\n-----------TEST : CD with no arguments and errors --------------\n");
	envp[0] = "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:";
	envp[1] = "OLDPWD=/Users/yuliia/Desktop/minishell";
	envp[2] = "HOME=/Users/yuliia";
	envp[3] = "SHLVL=1";
	envp[4] = "PWD=julia/my_lolder_with_dream";
	envp[5] = "CLASSIC_VAR=classic_value";
	envp[6] = NULL;

	arguments[0] = NULL;
	new_envp = enviromental_variable_function(envp, "cd", arguments);
	
	assert(strcmp(new_envp[0], "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:") == 0);
	assert(strcmp(new_envp[1], "HOME=/Users/yuliia") == 0);
	assert(strcmp(new_envp[2], "SHLVL=1") == 0);
	assert(strcmp(new_envp[3], "PWD=/Users/yuliia") == 0);
	assert(strcmp(new_envp[4], "CLASSIC_VAR=classic_value") == 0);
	assert(strcmp(new_envp[5], "OLDPWD=julia/my_lolder_with_dream") == 0);
	if (new_envp[6] != NULL)
		printf("nope, there is smth instead of NULL:\n%s\n", new_envp[6]);
}


void test_no_arg(void)
{
	char *envp[10];
	char **new_envp;

	printf("\n-----------TEST : no arguments--------------\n");
	envp[0] = "HOME=/Users/yuliia";
	envp[1] = "OLDPWD=/Users/yuliia/Desktop/minishell";
	envp[2] = "PATH=/opt/homebrew/bin:/opt/homebrew/sbin:";
	envp[3] = "SHLVL=1";
	envp[4] = "PWD=julia/my_lolder_with_dream";
	envp[5] = "CLASSIC_VAR=classic_value";
	envp[6] = NULL;

	new_envp = enviromental_variable_function(envp, "export", NULL);
	while (*new_envp != NULL)
	{
		printf("\n%s", *new_envp);
		new_envp++;
	}
	//answer \
	declare -x CLASSIC_VAR="classic_value" \
	declare -x HOME="/Users/yuliia" \
	declare -x PATH="/opt/homebrew/bin:/opt/homebrew/sbin:" \
	declare -x PWD="julia/my_lolder_with_dream" \
	declare -x SHLVL="1"
}

int	test_change_variable(void)
{
	char *command;

	command = "export";
	test_no_arg();
	correct_input(command);
	incorrect_inp1(command);
	

	command = "unset";
	correct_input(command);
//	incorrect_inp1(command);
//
//	test_cd();

	return 0;
}
