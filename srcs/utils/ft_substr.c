/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:26:30 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/13 13:50:52 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_strlen.h"

static void	fill(char const *s, size_t len, char *str, size_t start)
{
	size_t	i;
	size_t	x;

	x = ft_strlen(s);
	i = 0;
	while (start < x && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			x;

	if (!s && len > 0)
		return (NULL);
	x = ft_strlen(s);
	if (len > x)
		len = x;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		exit(1);
	if (start >= x)
	{
		str[0] = '\0';
		return (str);
	}
	fill(s, len, str, start);
	return (str);
}
