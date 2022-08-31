//
//  old_code.c
//  minishell_xcd
//
//  Created by Julia Demura on 29/08/2022.
//

#include <stdio.h>
//
//
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
