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
		return (NULL);
	ft_bzero(memory, (nmeb * size));
	return (memory);
}