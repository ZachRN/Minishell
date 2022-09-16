//
//  echo.c
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#include "echo.h"
#include "builtin_utils.h"
#include <stdlib.h>

#include <stdio.h>

int	check_synopsis_alter_array(char **argc)
{
	int i;

	i = 1;
	if (compare_str(argc[1], "-n") == FLS)
		return (0);
	else if (argc[i] == NULL)
		return (0);
	while (argc[i] != NULL && compare_str(argc[i], "-n") == TRU)
		i++;
	return (i - 1);
}

int	echo_builtin(char **argc, int fd)
{
	int i;
	int skip_n;

	i = 1;
	skip_n = check_synopsis_alter_array(argc);
	i += skip_n;
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
