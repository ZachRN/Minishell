/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:50:32 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 21:28:46 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_search.h"
#include "built_in_set.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

//	R_OK, W_OK, and X_OK test whether the file exists
//and grants read, write, and execute permissions, respectively.
int	check_assess_to_file(const char *path)
{
	if (path == NULL)
		return (0);
	if (access(path, F_OK) < 0)
	{
		write_str_fd("minishell: ", STDERR_FILENO);
		write_str_fd(path, STDERR_FILENO);
		write_str_fd(": No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
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
	char	*joined_command;
	int		i;

	correct_path = NULL;
	if (access(command, R_OK) == 0)
	{
		correct_path = strdup_till_char(command, '\0');
		return (correct_path);
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

char	**find_possible_path_options_from_envp(char **env)
{
	int		i;
	char	**possible_pathes;

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

char	*find_command_path(t_cmd cmd, char **envp)
{
	char	**possible_path;

	if (cmd.command == NULL)
		return (NULL);
	possible_path = find_possible_path_options_from_envp(envp);
	if (cmd.command[0] != '\0')
		cmd.cmd_path = find_path(cmd.command, possible_path);
	if (!cmd.cmd_path)
	{
		write_str_fd("minishell: ", STDERR_FILENO);
		write_str_fd(cmd.command, STDERR_FILENO);
		write_str_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	free_my_lines(possible_path);
	return (cmd.cmd_path);
}
