//
//  builtin_utils.h
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#ifndef builtin_utils_h
#define builtin_utils_h

#include "utils.h"

typedef enum	e_comm_n
{
	ECHO = 0,
	CD = 1,
	PWD = 2,
	EXPORT = 3,
	ENV = 4,
	UNSET = 5,
	EXIT = 6
}				t_comm_n;

typedef struct	s_env_struct
{
	t_comm_n comm_n;
	char **envp;
	char **new_envp;
	char **arguments;
	char *command;
	int num_var;
	int n_arguments;
	int envvar_repeat;
}				t_env_struct;

int is_valid_envp_name(const char *name);
char **fill_nulls(int i, int len, char **m_envp);
char **allocate_env_array_without_str(char **envp, int len, const char *str);
int	number_var_in_list(char **envp, const char *str);

#endif /* builtin_utils_h */
