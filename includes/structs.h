#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_parse
{
    char			*cmd;
    char			**args;
	char			*outfile;
	int				append;
	char			*infile;
	char			*heredoc;
    struct s_parse	*next;
}				t_parse;

typedef struct s_env
{
    char			*var_name;
    char			*var_content;
    char			*var_together;
    struct s_env	*next;
}               t_env;


#endif