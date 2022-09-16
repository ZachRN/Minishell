//
//  builtin_utils.c
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#include "builtin_utils.h"
#include <stdlib.h>

void	write_not_a_valid_identifier(const char *command, const char *argument, int fd)
{
	write_one_char_fd(fd, '\n');
	write_str_fd("Minishell : ", fd);
	write_str_fd(command, fd);
	write_str_fd(" : ", fd);
	write_str_fd(argument, fd);
	write_str_fd(" : not a valid identifier", fd);
	write_one_char_fd(fd, '\n');
}

int is_valid_envp_name(const char *name)
{
	if (is_number(name[0]) == TRU)
		return (FLS);
	else if (is_char(name[0]) == FLS && name[0] != '_')
		return (FLS);
	return (TRU);
}

char	**fill_nulls(int i, int len, char **m_envp)
{
	while (i < len)
	{
		m_envp[i] = NULL;
		i++;
	}
	m_envp[i] = NULL;
	return (m_envp);
}

char **allocate_env_array_without_str(char **envp, int len, const char *str)
{
	char **m_envp;
	int i;

	m_envp = malloc(sizeof(char *) * (len + 1));
	if (m_envp == NULL)
		exit(1);
	i = 0;
	while (*envp != NULL)
	{
		if (compare_str_till_char(*envp, str, '=') == TRU)
		{
			envp++;
			if (*envp == NULL)
				break ;
		}
		m_envp[i] = ft_strdup(*envp);
		if (m_envp[i] == NULL)
			exit(1);
		i++;
		envp++;
	}
	m_envp = fill_nulls(i, len, m_envp);
	return (m_envp);
}

int	number_var_in_list(char **envp, const char *str) /// will ret 0 only in case of no var in the list
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (compare_str_till_char(envp[i], str, '=') == TRU)
			return (i + 1);
		else
			i++;
	}
	return (FLS);
}
