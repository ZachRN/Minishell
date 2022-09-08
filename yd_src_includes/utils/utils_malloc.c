//
//  utils_malloc.c
//  x_mini
//
//  Created by Julia Demura on 06/09/2022.
//

#include "utils_malloc.h"

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

char	*strdup_till_char(char *str, char c)
{
	int		i;
	char	*s2;
	int		len;

	len = strlen_till_char(str, c);
	i = 0;
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	while (i < len)
	{
		s2[i] = str[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	new_str = (char *)malloc(((string_len(s1) + string_len(s2)) + 1)
			* sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (i < string_len(s1))
	{
		new_str[i] = s1[i];
		i++;
	}
	while (j < string_len(s2))
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
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
