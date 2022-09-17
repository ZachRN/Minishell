//
//  path_search.h
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//

#ifndef path_search_h
#define path_search_h

#include "form_exec_struct.h"

int		check_assess_to_file(const char *path);
char	**find_possible_path_options_from_envp(char **env);
char	*find_path(char *command, char **possibl_paths);
char	*find_command_path(t_cmd cmd, char **envp);

#endif /* path_search_h */
