/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:35:51 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:37:29 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

# include "utils.h"
# include "form_exec_struct.h"

typedef enum e_comm_n
{
	ECHO = 0,
	CD = 1,
	PWD = 2,
	EXPORT = 3,
	ENV = 4,
	UNSET = 5,
	EXIT = 6
}				t_comm_n;

typedef struct s_env_struct
{
	t_comm_n	comm_n;
	char		**envp;
	char		**new_envp;
	char		**arguments;
	char		*command;
	int			num_var;
	int			n_arguments;
	int			envvar_repeat;
	int			fd_chosen;
	int			last_error;
	int			prev_builtin_err;
}				t_env_struct;

void	write_not_a_valid_identifier(const char *command,
			const char *argument, int fd);
int		is_valid_envp_name(const char *name);
char	**fill_nulls(int i, int len, char **m_envp);
char	**allocate_env_array_without_str(char **envp, int len, const char *str);
int		number_var_in_list(char **envp, const char *str);

#endif /* builtin_utils_h */
