//
//  built_in_set.h
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#ifndef built_in_set_h
#define built_in_set_h

#include "builtin_utils.h"

int	if_is_builtin_command(char *str, char **array_built_in);
char **built_in_commands(t_env_struct *data);
char **enviromental_variable_function(char **envp, char *command, char **arguments, t_fd fd);

#endif /* built_in_set_h */
