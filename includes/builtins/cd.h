/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:37:38 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:38:39 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "builtin_utils.h"

typedef struct s_env_indexes
{
	int	homevar;
	int	pwd;
	int	oldpwd;
}				t_env_indexes;

char	**cd_builtin(t_env_struct *data);

//in cd2.c
int		go_to_other_folder(const char *path, int fd);
int		get_new_len(char *name, char *value);
char	*join_varname_value_malloc(char *name, char *value);
int		change_pwd_value(t_env_indexes i, t_env_struct *data);
int		change_var_value_based_on_indexes(int i_oldpwd, int i_pwd,
			t_env_struct *data);

#endif /* cd_h */
