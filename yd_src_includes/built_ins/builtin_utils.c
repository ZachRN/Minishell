//
//  builtin_utils.c
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#include "builtin_utils.h"

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
			return (0); //false, not eqial str
	}
	return (1); //true, eqial str
}

int	string_len(char *str)
{
	int res;

	if (!str)
		return FLS; // 0
	res = 0;
	while (str[res] != '\0')
	{
		res++;
	}
	return (res);
}

int	print_till_n(char *str, int n)
{
	int i;

	i = 0;
	if (!str)
		return FLS;
	while (i < n)
	{
		write(1, &str[i], 1);
		i++;
	}
	return TRU;
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
	new_var_array = malloc(sizeof(char *) * (new_len) + 1);
	while (i < len_of_old_arr)
	{
		new_var_array[i] = array[i];
		i++;
	}
	new_var_array[new_len] = NULL;
	free(array);
	return (new_var_array);
}

int	find_arr_len(char **arr) /// please all custom made arrays - null terminated and strings \0 terminated
{
	int res;

	res = 0;
	while (arr[res] != NULL)
		res++;
	return (res);
}
