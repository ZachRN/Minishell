#include <unistd.h>
#include <ft_strdup.h>
#include <ft_strncmp.h>
#include <structs.h>
#include <ft_split.h>
#include <ft_strjoin.h>
#include <stdio.h>

static char *check_absolute_path(char *cmd, char **env)
{
	if (!env)
		return (NULL);
	while (ft_strncmp(*env, "PWD=", 4))
		env++;
	chdir((*env) + 4);
	if (access(cmd, F_OK) == 0)
		return ft_strdup(cmd);
	return (NULL);
}

static int is_rel_abs_path(char *cmd)
{
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "../", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "/", 1) == 0)
		return (1);
	return (0);
}

static char	*check_path_paths(char **paths, char *cmd)
{
	char	*store_command;
	char	*possible_env_path;
	int		i;

	i = 0;
	store_command = ft_strjoin("/", cmd);
	while (*(paths + i))
	{
		possible_env_path = ft_strjoin(*(paths + i), store_command);
		if (access(possible_env_path, F_OK) == 0)
		{
			if (store_command)
				free(store_command);
			return (possible_env_path);
		}
		else if (possible_env_path)
			free(possible_env_path);
		i++;
		possible_env_path = NULL;
	}
	if (store_command)
		free(store_command);
	return (possible_env_path);
}

int		is_built_in(char *str)
{
	int i;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	if ((ft_strncmp(str, "echo", 5) == 0) || 
		(ft_strncmp(str, "cd", 3) == 0) ||
		(ft_strncmp(str, "pwd", 4) == 0) || 
		(ft_strncmp(str, "export", 7) == 0) ||
		(ft_strncmp(str, "unset", 6) == 0) || 
		(ft_strncmp(str, "env", 3) == 0) ||
		(ft_strncmp(str, "exit", 5) == 0))
		return (1);
	return (0);
}
char    *find_cmd_path(char *cmd, char **env)
{
    char **possible_paths;
	char *to_return;

    if (!cmd)
        return (NULL);
    if (is_rel_abs_path(cmd))
        return (check_absolute_path(cmd, env));
	else if (is_built_in(cmd))
		return (ft_strdup(cmd));
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	possible_paths = ft_split(*env + 5, ':');
	if (!possible_paths)
		return (NULL);
	to_return = (check_path_paths(possible_paths, cmd));
	free_my_lines(possible_paths);
	return (to_return);
}