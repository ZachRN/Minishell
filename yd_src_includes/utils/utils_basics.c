//
//  utils_basics.c
//  x_mini
//
//  Created by Julia Demura on 06/09/2022.
//

#include "utils_basics.h"

int	string_len(const char *str)
{
	int res;

	if (!str)
		return (-1);
	res = 0;
	while (str[res] != '\0')
	{
		res++;
	}
	return (res);
}
//

int	strlen_till_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
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
