//
//  path_search.c
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//

#include "path_search.h"
#include "built_in_set.h" //should incl data with envp
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

char	*check_correct_path(char *command, char *possible_path)
{
	char	*new_path;

	new_path = ft_strjoin(possible_path, command);
	if (new_path == NULL)
		return (NULL);
	if (access(new_path, R_OK) == 0)
		return (new_path);
	else
	{
		free(new_path);
		return (NULL);
	}
	return (NULL);
}

char	*find_path(char *command, char **possibl_paths)
{
	char	*correct_path;
	char	*joined_command;
	int		i;

	correct_path = NULL;
	if (access(command, R_OK) == 0)
	{
		correct_path = strdup_till_char(command, '\0');
		return(correct_path);
	}
	joined_command = ft_strjoin("/", command);
	if (joined_command == NULL)
		exit(1);
	i = 0;
	while (possibl_paths[i] != NULL)
	{
		correct_path = check_correct_path(joined_command, possibl_paths[i]);
		if (correct_path == NULL)
			i++;
		else
			break ;
	}
	free(joined_command);
	return (correct_path);
}

char **find_possible_path_options_from_envp(char **env)
{
	int	i;
	char **possible_pathes;

	i = 0;
	possible_pathes = NULL;
	while (env[i] && !possible_pathes)
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			possible_pathes = ft_split(&env[i][5], ':');
		i++;
	}
	return (possible_pathes);
}
