//
//  builtin_utils.h
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#ifndef builtin_utils_h
#define builtin_utils_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum e_status
{
	FLS = 0,
	TRU = 1,
	ERR = -1
}			t_status;
//
////◦ cd with only a relative or absolute path
////◦ pwd with no options
////◦ export with no options
////◦ unset with no options
////◦ env with no options or arguments
////◦ exit with no options

int	compare_str(char *str1, char *str2);
int	string_len(char *str);
int	print_till_n(char *str, int n);
int	write_one_char_fd(int fd, char c);
char	**array_realloc(char **array, int len_of_old_arr, int new_len);
int	find_arr_len(char **arr); /// please all custom made arrays - null terminated and strings \0 terminated


#endif /* builtin_utils_h */
