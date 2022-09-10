//
//  path_search.c
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//

#include "path_search.h"
#include "built_in_set.h" //should incl data with envp
#include "split.h"
#include <stdlib.h>
#include <unistd.h>

char **find_possible_path_options_from_envp(char **env)
{
	int	i;
	char **possible_pathes;

	i = 0;
	while (env[i] != NULL)
	{
		if (check_word("PATH=/", 6, env[i]) == 1)
		{
			while (*env[i] != ':' && *env[i] != '\0')
				env[i]++;
			break ;
		}
		i++;
	}
	if (env[i] != NULL)
	{
		possible_pathes = ft_split(env[i], ':');
		if (possible_pathes == NULL)
			exit(1);
	}
	return (NULL);
}

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
	int		i;

	correct_path = NULL;
	if (access(command, R_OK) == 0)
	{
		correct_path = strdup_till_char(command, '\0');
		return(correct_path);
	}
	command = ft_strjoin("/", command);
	if (command == NULL)
		exit(1);
	i = 0;
	while (possibl_paths[i] != NULL)
	{
		correct_path = check_correct_path(command, possibl_paths[i]);
		if (correct_path == NULL)
			i++;
		else
			break ;
	}
	free(command);
	return (correct_path);
}
