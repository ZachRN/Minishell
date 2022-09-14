/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:24:32 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/13 13:50:06 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n)
	{
		*str = '\0';
		str++;
		n--;
	}
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*memory;

	if (nmeb == 0 || size == 0)
	{
		nmeb = 1;
		size = 1;
	}
	memory = malloc(nmeb * size);
	if (!memory)
		exit(1);
	ft_bzero(memory, (nmeb * size));
	return (memory);
}
