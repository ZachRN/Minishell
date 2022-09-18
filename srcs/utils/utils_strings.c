/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:08:05 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:08:38 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_strings.h"
#include "utils_basics.h"
#include <stdlib.h>

int	compare_str(const char *str1, const char *str2)
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
			return (FLS);
	}
	return (TRU);
}

int	check_word(const char *word, int word_len, const char *str)
{
	int	i;

	i = 0;
	while (i < word_len && (word[i] != '\0' || str[i] != '\0'))
	{
		if (word[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

int	compare_str_till_char(const char *env_name, const char *argument, char c)
{
	if (env_name == NULL || argument == NULL)
		return (0);
	while ((*env_name || *argument) && *env_name != c)
	{
		if (*env_name == *argument)
		{
			env_name++;
			argument++;
		}
		else
			return (FLS);
	}
	if (*env_name == c && (*argument == c || *argument == '\0'))
		return (TRU);
	else
		return (FLS);
}

int	find_char_in_str(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
