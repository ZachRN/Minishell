//
//  builtin_utils.h
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#ifndef builtin_utils_h
#define builtin_utils_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum e_status
{
	FLS = 0,
	TRU = 1,
	ERR = -1
}			t_status;

typedef enum	e_comm_n
{
	ECHO = 0,
	CD = 1,
	PWD = 2,
	EXPORT = 3,
	ENV = 4,
	UNSET = 5,
	EXIT = 6
}				t_comm_n;

typedef struct	s_env_data
{
	t_comm_n comm_n;
	char **envp;
	char **new_envp;
	char **arguments;
	char *command;
	int num_var;
	int n_arguments;
	int envvar_repeat;
}				t_env_data;

int is_valid_envp_name(char *name);
char **allocate_env_array_without_str(char **envp, int len, char *str);
char	*ft_strdup(const char *s1);
void free_array_of_str(char **array);
int	number_var_in_list(char **envp, char *str); //, int n
int find_char_in_str(char c, char *str);
int	is_char(char c);
int	is_number(char c);
char	*copy_str_till_n(char *str1, int n);
int	compare_str_till_n(char *str1, char *str2, int len_str1);
int	compare_str_till_char(char *str1, char *str2, char c);
int	compare_str(char *str1, char *str2);
int	string_len(char *str);
int	write_one_char_fd(int fd, char c);
int	write_str_fd(char *str, int fd);
char	**array_realloc(char **array, int len_of_old_arr, int new_len);
int	find_arr_len(char **arr);


#endif /* builtin_utils_h */
