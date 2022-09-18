/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:15:40 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 11:16:45 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "builtin_utils.h"
#include <stdlib.h>

#include <stdio.h>

int	find_nnnnn(char *str)
{
	while (str && str[0] != '\0')
	{
		if (str[0] == '-' && str[1] == 'n')
		{
			str += 2;
			while (*str != '\0' && *str == 'n')
				str++;
		}
		if (*str == '\0')
			return (TRU);
		else
			return (FLS);
	}
	return (FLS);
}

int	check_synopsis_alter_array(char **argc)
{
	int	i;

	i = 0;
	if (argc == NULL)
		return (0);
	while (argc[i] != NULL && (compare_str(argc[i], "-n") == TRU
			|| find_nnnnn(argc[i]) == TRU))
	{
		i++;
	}
	return (i);
}

int	echo_builtin(char **argc, int fd)
{
	int	i;
	int	skip_n;

	i = 0;
	skip_n = check_synopsis_alter_array(argc);
	i += skip_n;
	if (argc == NULL)
	{
		write_one_char_fd(fd, '\n');
		return (0);
	}
	while (argc[i] != NULL)
	{
		write_str_fd(argc[i], fd);
		if (argc[i + 1] != NULL)
			write_one_char_fd(fd, ' ');
		i++;
	}
	if (skip_n == 0)
		write_one_char_fd(fd, '\n');
	return (0);
}
