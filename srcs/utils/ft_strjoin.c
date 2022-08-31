/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:26:08 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/31 13:26:09 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_strlen.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		x;
	int		y;
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	y = 0;
	while (s1[y] != '\0')
	{
		s3[y] = s1[y];
		y++;
	}
	x = 0;
	while (s2[x] != '\0')
	{
		s3[y] = s2[x];
		x++;
		y++;
	}
	s3[y] = '\0';
	return (s3);
}
