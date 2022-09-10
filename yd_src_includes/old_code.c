//
//  old_code.c
//  minishell_xcd
//
//  Created by Julia Demura on 29/08/2022.
//

#include <stdio.h>
//
//


//char	**realloc_arr_include_str(char **arr, const char *str, int len)
//{
//	char **m_arr;
//	int i;
//
//	m_arr = malloc(sizeof(char *) * (len + 1));
//	if (m_arr == NULL)
//		exit(-1);
//	i = 0;
//	while (arr[i] != NULL)
//	{
//		m_arr[i] = ft_strdup((const char *)arr[i]);
//		if (m_arr[i] == NULL)
//			exit(-1);
//		i++;
//	}
//	m_arr[i] = ft_strdup(str);
//	if (m_arr[i] == NULL)
//		exit(-1);
//	m_arr[i + 1] = NULL;
//	return (m_arr);
//}


//
//char 	**shift_array_delete_var(char **envp, char *str)
//{
//	int i;
//	int found_old_pwd;
//
//	i = 0;
//	found_old_pwd = 0;
//	while (envp[i] != NULL)
//	{
//		if (compare_str_till_n(str, envp[i], string_len(str)) == TRU)
//		{
//			found_old_pwd = 1;
//			break ;
//		}
//		i++;
//	}
//	while (found_old_pwd == 1 && envp[i + 1] != NULL)
//	{
//		envp[i] = envp[i + 1];
//		i++;
//	}
//	if (found_old_pwd == 1)
//		envp[i] = NULL;
//	return (envp);
//}
