#include <stdlib.h>

static int  ft_strlen(const char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		strlen;
	int		i;

    if (!s)
        return (NULL);
	strlen = ft_strlen(s);
	str = malloc(sizeof(char) * (strlen + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < strlen)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
