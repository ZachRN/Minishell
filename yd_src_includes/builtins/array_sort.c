//
//  array_sort.c
//  minishell_xcd
//
//  Created by Julia Demura on 26/08/2022.
//

#include "array_sort.h"

void	printtest_arr(char **arr, char *name)
{
	int j = 0;
	printf("\n%s START\n\n", name);
	while (arr[j] != NULL)
	{
		printf("%s\n", arr[j]);
		j++;
	}
	printf("\n%s END\n", name);
}

int write_export_no_arguments(char **array, int fd)
{
	int i;
	int j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		write_str_fd("declare -x ", fd);
		while (array[i][j] != '\0') ///		write_str_fd(array[i], fd);
		{
			if (array[i][j - 1] == '=')
				write_one_char_fd(fd, '"');
			write_one_char_fd(fd, array[i][j]);
			j++;
		}
		if (array[i][j] == '\0')
			write_one_char_fd(fd, '"');
		write_one_char_fd(fd, '\n');
		i++;
	}
	return (0);
}

int	custom_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	signed int		difference;

	i = 0;
	while (((unsigned char)s1[i] != '\0' || (unsigned char)s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			difference = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (difference);
		}
		i++;
	}
	return (0);
}

char **swap_strings(char **array, int j, char *temp)
{
	temp = array[j];
	array[j] = array[j + 1];
	array[j + 1] = temp;
	return (array);
}

char **array_sort_awrite_fd(char **array, int arr_size, int fd)
{
	int i;
	int j;
	char temp[4096];

	i = 0;
	while (i < arr_size)
	{
		j = 0;
		while (j < arr_size && array[j + 1] != NULL)
		{
			//compare 2 strings, swap if j > j+1
			if (custom_strcmp(array[j], array[j + 1]) > 0)
			{
				//swap these 2
				array = swap_strings(array, j, temp);
			}
			j++;
		}
		i++;
	}
	write_export_no_arguments(array, fd);
	return (array);
}
