#include <unistd.h>
#include <ft_strdup.h>
#include <stdlib.h>
#include <stdio.h>

char	**free_lines(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**copy_env_list(char **to_return, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		to_return[i] = ft_strdup(env[i]);
		if (!to_return[i])
			return (free_lines(to_return));
		i++;
	}
	to_return[i] = NULL;
	return (to_return);
}

int	get_size_of_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	env_vars_copy_display(char **str)
{
	while (*str)
	{
		printf("%s\n", *str);
		str++;
	}
}
char	**env_copy(char **env)
{
	char	**to_return;
	int		size;

	if (!env)
		return (NULL);
	size = get_size_of_env(env);
	to_return = (char **)malloc((size + 1) * sizeof(char *));
	if (!to_return)
		return (NULL);
	to_return = copy_env_list(to_return, env);
	return (to_return);
}