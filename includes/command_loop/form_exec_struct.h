/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_exec_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:43:29 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:45:32 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_EXEC_STRUCT_H
# define FORM_EXEC_STRUCT_H

# include "structs.h"
# include <sys/types.h>
# include <unistd.h>

typedef enum e_infile_src
{
	STDIN = 0,
	INFILE = 1,
	HEREDOC = 2
}				t_infile_src;

typedef enum e_type
{
	BUILTIN = 0,
	NORMAL = 1
}				t_type;

typedef struct s_fd_two
{
	int	storage;
	int	pipe[2];
}			t_fd_two;

typedef struct t_cmd
{
	char	**cmd_args;
	char	*cmd_path;
	char	*command;
	t_type	type;
}	t_cmd;

typedef struct s_param
{
	t_cmd			cmd;
	int				wait_status;
	int				res_wait_status;
	pid_t			child_pid;
	char			*path_infile;
	char			*path_outfile;
	int				param_index;
	int				append;
	char			*heredoc;
	int				inlile_heredoc_flag;
	t_infile_src	in_flag;
	int				last_error;
}				t_param;

typedef struct s_exec
{
	t_param	*params;
	char	**envp;
	char	**upd_envp;
	int		comm_number;
	int		last_error;
	int		index;
}				t_exec;

t_param	*fill_exec_struct(t_parse *head, int size);
int		if_built_in(const char *command);
int		linked_list_size(t_parse *head);
t_cmd	initiate_cmd_struct(char **args, char *comm_name);
t_param	initiate_each_param(t_parse *current, int i);

#endif /* form_exec_struct_h */
