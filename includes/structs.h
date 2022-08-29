/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:53:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/24 17:06:56 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*I'm only going to comment on the enum here as it was designed in a very
particular manner
I made it so that, All the Special characters which can error very easily such 
as < << >> > | came first, whcih allows me to check token_types using < 
because those will also flag certain conditions. I then set the " and ' next
as their are times where I only need $ and the regular identifier.

Essentially I made it so taht instead of doing a function is_in I can just do
a less than x token in an if statement as I found taht a bit nicer.
*/
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

typedef struct s_heredoc
{
	int		has_quote;
	char	*End;
}				t_heredoc;

typedef struct s_parse
{
	char			*cmd;
	char			**args;
	char			*outfile;
	int				append;
	char			*infile;
	int				heredoc_pipe;
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
	int				start;
	int				end;
	char			*content;
	struct s_lexer	*next;
	struct s_lexer	*prev;	
}				t_lexer;

typedef struct s_together
{
	t_parse		*head;
	char		**env_array;
	int			last_error;
	t_lexer		*lex_head;
}				t_together;

typedef struct s_quote
{
	int	double_quote;
	int	single_quote;
	int	prev_token;
}	t_quote;

typedef struct s_pack
{
	int i;
	char *str;
}				t_pack;

typedef struct s_lex_parse_pack
{
	t_parse	*to_add;
	t_lexer *to_search;
	int		no_file;
}				t_l_p_pack;

#endif