/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:53:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/18 15:45:18 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum e_tokens
{
	Greater = 1,
	Double_Greater,
	Lesser,
	Double_Lesser,
	Pipe,
	Quote,
	Double_Quote,
	Expand,
	Iden
};

typedef struct s_parse
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
}				t_env;

typedef struct s_lexer
{
	int				token_id;
	int				token_type;
	int				pos_start;
	int				pos_end;
	char			*content;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_together
{
	t_parse		*head;
	char		**env_array;
	int			last_error;
}				t_together;

#endif