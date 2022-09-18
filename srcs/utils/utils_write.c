/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:08:46 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:09:03 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_write.h"
#include "utils_basics.h"
#include <unistd.h>

int	write_one_char_fd(int fd, char c)
{
	write(fd, &c, 1);
	return (0);
}

int	write_str_fd(const char *str, int fd)
{
	int	i;
	int	n;

	i = 0;
	n = string_len(str);
	if (!str)
		return (FLS);
	while (i < n)
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (TRU);
}
