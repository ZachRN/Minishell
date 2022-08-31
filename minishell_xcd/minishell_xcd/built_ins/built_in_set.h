//
//  built_in_set.h
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#ifndef built_in_set_h
#define built_in_set_h


#include "echo.h"
#include "pwd.h"
#include "env.h"
#include "export.h"
#include "unset.h"
#include "cd.h"
#include "exit.h"

int	if_is_builtin_command(char *str, char **array_built_in);
//char **built_in_commands(char **envp, char *command, char **arguments);
char **built_in_commands(t_env_data *data);


#endif /* built_in_set_h */
