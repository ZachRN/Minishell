#include <unistd.h>
#include <stdlib.h>

static int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

	if (!s)
		return (NULL);
	x = ft_strlen(s);
	if (len > x)
		len = x;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (start >= x)
	{
		str[0] = '\0';
		return (str);
	}
	fill(s, len, str, start);
	return (str);
}