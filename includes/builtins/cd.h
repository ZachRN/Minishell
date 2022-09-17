//
//  cd.h
//  minishell_xcd
//
//  Created by Julia Demura on 24/08/2022.
//

#ifndef cd_h
#define cd_h

#include "builtin_utils.h"

typedef struct	s_env_indexes
{
	int homevar;
	int pwd;
	int oldpwd;
}				t_env_indexes;

char**	cd_builtin(t_env_struct *data);

#endif /* cd_h */
