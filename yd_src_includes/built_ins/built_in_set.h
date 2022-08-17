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

int	if_is_builtin_command(char *str);

#endif /* built_in_set_h */
