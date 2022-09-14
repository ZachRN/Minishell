//
//  form_exec_struct.h
//  mini_codam
//
//  Created by Yuliia Demura on 9/6/22.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#ifndef FORM_EXEC_STRUCT_H
# define FORM_EXEC_STRUCT_H

# include "path_search.h"
# include <sys/types.h>
# include <unistd.h>

enum e_redirect_in
{
	No_Infile = 0,
	Infile,
	Heredoc
};

typedef enum e_infile_src
{
	STDIN = 0,
	INFILE = 1,
	HEREDOC = 2
}				t_infile_src;

typedef struct s_lexer
{
	int				token_id;
	int				token_type;
	int				start;
	int				end;
	char			*content;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_parse
{
	char			*cmd;
	char			**args;
	char			*outfile;
	int				append;
	char			*infile;
	int				hd_pipe;
	struct s_parse	*next;
	int				rd_in;
}				t_parse;

typedef struct s_together
{
	t_parse		*head;
	char		**env_array;
	int			last_error;
	t_lexer		*lex_head;
}				t_together;

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	heredoc;
	int	temp_file;
	int	pipe[2];
	int	rdr_infile;
	int	rdr_outfile;
}	t_fd;

typedef struct t_cmd
{
	char	**cmd_args;
	char	*cmd_path;
	char	*command;
}	t_cmd;

typedef struct s_param
{
	t_cmd			cmd;
	t_fd			fd;
	int				wait_status;
	int				res_wait_status;
	pid_t			child_pid;
	char			*path_infile;
	char			*path_outfile;
	int				param_index;
	int				append;
	int				inlile_heredoc_flag;
	t_infile_src	in_flag;
}				t_param;

typedef struct s_exec
{
	t_param	*params;
	char	**envp;
	int		comm_number;
	int		last_error;
	int		index; ///	not sure if needed not initiated yet
}				t_exec;

t_exec	form_input_for_execution(char **envp, t_together *input);

#endif /* form_exec_struct_h */
