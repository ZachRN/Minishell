//
//  path_search.h
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//

#ifndef path_search_h
#define path_search_h

#include "built_in_set.h" //should incl data with envp
#include "split.h"

char	**find_possible_path_options_from_envp(char **env);
char	*find_path(char *command, char **possibl_paths);

#endif /* path_search_h */
