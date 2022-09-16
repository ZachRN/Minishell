//
//  form_exec_struct.h
//  mini_codam
//
//  Created by Yuliia Demura on 9/6/22.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#ifndef form_exec_struct_h
#define form_exec_struct_h

#include "path_search.h"
#include "structs.h"
#include <sys/types.h>
#include <unistd.h>

typedef enum	e_infile_src
{
	STDIN = 0,
	INFILE = 1,
	HEREDOC = 2
}				t_infile_src;

typedef enum	e_type
{
	BUILTIN = 0,
	NORMAL = 1
}				t_type;

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int heredoc;
	int	temp_file;
	int	pipe[2];
}	t_fd;

typedef struct t_cmd
{
	char	**cmd_args;
	char	*cmd_path;
	char	*command;
	t_type type;
}	t_cmd;

typedef struct	s_param
{
	t_cmd	cmd;
	t_fd	fd;
	int		wait_status;
	int		res_wait_status;
	pid_t	child_pid;
	char	*path_infile;
	char	*path_outfile;
	int		param_index;
	int		append;
	int		inlile_heredoc_flag;
	t_infile_src in_flag;
	int		last_error;
}				t_param;

typedef struct	s_exec
{
	t_param *params;
	char	**envp;
	char	**upd_envp;
	int		comm_number;
	int		last_error;
	int		index; ///	not sure if needed not initiated yet
}				t_exec;

t_exec form_input_for_execution(char **envp, t_together *input);

#endif /* form_exec_struct_h */
