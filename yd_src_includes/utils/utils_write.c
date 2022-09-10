//
//  utils_write.c
//  x_mini
//
//  Created by Julia Demura on 06/09/2022.
//

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
	int i;
	int n;

	i = 0;
	n = string_len(str);
	if (!str)
		return FLS;
	while (i < n)
	{
		write(fd, &str[i], 1);
		i++;
	}
	return TRU;
}
