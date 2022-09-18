/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:05:13 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 10:07:45 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_sort.h"
#include "utils.h"
#include <stdio.h>

int	write_export_no_arguments(char **array, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		write_str_fd("declare -x ", fd);
		while (array[i][j] != '\0')
		{
			if (array[i][j - 1] == '=')
				write_one_char_fd(fd, '"');
			write_one_char_fd(fd, array[i][j]);
			j++;
		}
		if (array[i][j] == '\0')
			write_one_char_fd(fd, '"');
		write_one_char_fd(fd, '\n');
		i++;
	}
	return (0);
}

int	custom_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	signed int		difference;

	i = 0;
	while (((unsigned char)s1[i] != '\0' || (unsigned char)s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			difference = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (difference);
		}
		i++;
	}
	return (0);
}

char	**swap_strings(char **array, int j, char *temp)
{
	temp = array[j];
	array[j] = array[j + 1];
	array[j + 1] = temp;
	return (array);
}

char	**array_sort_awrite_fd(char **array, int arr_size, int fd)
{
	int		i;
	int		j;
	char	temp[4096];

	i = 0;
	while (i < arr_size)
	{
		j = 0;
		while (j < arr_size && array[j + 1] != NULL)
		{
			if (custom_strcmp(array[j], array[j + 1]) > 0)
			{
				array = swap_strings(array, j, temp);
			}
			j++;
		}
		i++;
	}
	write_export_no_arguments(array, fd);
	return (array);
}
