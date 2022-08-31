//
//  builtin_utils.c
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#include "builtin_utils.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*s2;

	i = 0;
	len = 0;
	while (s1[len] != '\0')
		len++;
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
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

char **allocate_env_array_without_str(char **envp, int len, char *str)
{
	char **m_envp;
	int i;

	m_envp = malloc(sizeof(char *) * (len + 1));
	if (m_envp == NULL)
		exit(-1);
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
			exit(-1);
		i++;
		envp++;
	}
	m_envp = fill_nulls(i, len, m_envp);
	return (m_envp);
}

void free_array_of_str(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	number_var_in_list(char **envp, char *str) /// will ret 0 only in case of no var in the list
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (compare_str_till_char(str, envp[i], '=') == TRU)
			return (i + 1);
		else
			i++;
	}
	return (FLS);
}

int find_char_in_str(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	is_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (TRU);
	return (FLS);
}

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (TRU);
	return (FLS);
}

char *copy_str_till_n(char *str, int n)
{
	char *new_str;
	int i;

	new_str = malloc(sizeof(char) * (n + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' || i < n)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

int	compare_str(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return (0);
	while (*str1 != '\0' || *str2 != '\0')
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
			return (FLS); //false, not eqial str
	}
	return (TRU); //true, eqial str
}

int	compare_str_till_char(char *str1, char *str2, char c)
{
	if (str1 == NULL || str2 == NULL)
		return (0);
	while ((*str1 || *str2) && *str1 != c)
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
			return (FLS); //false, not eqial str
	}
	if (*str1 == c && (*str2 == c || *str2 == '\0'))
		return (TRU);
	else
		return (FLS); //true, eqial str
}

int	compare_str_till_n(char *str1, char *str2, int n)
{
	if (str1 == NULL || str2 == NULL)
		return (0);
	while ((*str1 || *str2) && n > 0)
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
			n--;
		}
		else
			return (FLS); //false, not eqial str
	}
	return (TRU); //true, eqial str
}

int	string_len(char *str)
{
	int res;

	if (!str)
		return ERR; // 0
	res = 0;
	while (str[res] != '\0')
	{
		res++;
	}
	return (res);
}

int	write_one_char_fd(int fd, char c)
{
	write(fd, &c, 1);
	return (0);
}

int	write_str_fd(char *str, int fd)
{
	int i;
	int n;

	i = 0;
	n = string_len(str);
	if (!str)
		return FLS;
	while (i < n)
	{
		write(fd, &str[i], 1);
		i++;
	}
	return TRU;
}

char	**array_realloc(char **array, int len_of_old_arr, int new_len)
{
	char	**new_var_array;
	int 	i;

	i = 0;
	new_var_array = malloc(sizeof(char *) * ((new_len) + 1));
	if (new_var_array == NULL)
		return (NULL);
	while (i < len_of_old_arr)
	{
		new_var_array[i] = array[i];
		i++;
	}
	while (i < new_len + 1)
	{
		new_var_array[i] = NULL;
		i++;
	}
	return (new_var_array);
}

int	find_arr_len(char **arr) /// please all custom made arrays - null terminated and strings \0 terminated
{
	int res;

	res = 0;
	if (arr == NULL)
		return (0);
	while (arr[res] != NULL)
		res++;
	return (res);
}
