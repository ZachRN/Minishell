/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_start.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:45:09 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/10 13:50:04 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "structs.h"
#include "ft_strncmp.h"
#include "ft_strdup.h"
#include "ft_substr.h"
#include "ft_strjoin.h"
#include "lexer_clear.h"
#include "lexer_display.h"
#include "heredoc_line_parse.h"
#include "signal_handles.h"

t_lexer	*join_heredoc_quotes(t_lexer *head, t_heredoc *heredoc, char *input)
{
	t_lexer	*tail;
	char	*temp;
	char	*temp_two;

	tail = head->next;
	heredoc->has_quote = 1;
	while (tail)
	{
		if (tail->token_type == D_Quote || tail->token_type == Quote)
			break ;
		tail = tail->next;
	}
	temp = heredoc->end;
	temp_two = ft_substr(input, head->start + 1, tail->end - 1 - head->start);
	heredoc->end = ft_strjoin(temp, temp_two);
	free(temp);
	free(temp_two);
	return (tail);
}

t_lexer	*remove_heredoc_list(t_lexer *head, t_lexer *tail)
{
	while (head != tail)
		head = rm_one_from_lexer_list(head);
	head = rm_one_from_lexer_list(head);
	return (head);
}

t_lexer	*go_handle(t_lexer *lex_head, t_heredoc *heredoc, char *input)
{
	t_lexer	*tail;
	char	*temp;

	tail = lex_head->next;
	heredoc->end = ft_strdup("\0");
	while (tail)
	{
		if (tail->token_type == D_Quote || tail->token_type == Quote)
			tail = join_heredoc_quotes(tail, heredoc, input);
		else
		{
			temp = heredoc->end;
			heredoc->end = ft_strjoin(heredoc->end, tail->content);
			free(temp);
		}
		if (tail->next && ((tail->next->start - tail->end != 1)
				|| tail->next->token_type < Quote))
			break ;
		tail = tail->next;
	}
	return (remove_heredoc_list(lex_head, tail));
}

static int	quick_fix(int token, t_together *all, t_lexer *tail)
{
	if (token == Double_Lesser)
	{
		all->lex_head = tail;
		if (tail)
			token = tail->token_type;
	}
	return (token);
}

/*
Heredoc has code that it pulls from expansion since it ways in the same fashion
The reason we do heredoc before we actually do anythign else is because
$PATH for heredoc will not expand to its actual /bin/ whatever the rest is.
This function will also remove the << and heredoc identifiers from the
t_lexer linked list.

Therefore I call it first, and handle it before i expand it to stay true
to the way heredoc works in bash. Also to note when heredoc has "" or '' in it
to any regard, even when its not within it by joined by it, nothign within 
Heredoc will expand.

It will grab the EOF(end of file)
joining the quotes and all the things around it to form
the string that it needs to create for the EOF. It will then go into a child
process for one very specific reason, When you use SIG_INT (signal interrupt)
it acts differently in heredoc. It will cancel the entirety of the command
no matter what you typed in. Essentially killing it adn also not doing the rest
of the heredocs. Therefore I put it into a child process so taht I can return
an Error code that will notify us when it happens so that I can cancel the rest
of the line verfication and no doing with it.
*/

t_together	*handle_heredoc(char *input, t_together *all, t_l_p_pack *pack)
{
	t_heredoc	heredoc;
	t_lexer		*tail;
	int			token;

	tail = all->lex_head;
	token = tail->token_type;
	heredoc.end = NULL;
	heredoc.has_quote = 0;
	while (tail)
	{
		if (tail->token_type == Double_Lesser)
		{
			tail = go_handle(tail, &heredoc, input);
			pack->to_add->hd_pipe
				= parse_line_heredoc(all, &heredoc, pack->to_add);
			signal_director(MAIN_SIG);
		}
		else if (tail)
			tail = tail->next;
		token = quick_fix(token, all, tail);
		if ((tail && tail->token_type == Pipe) || pack->to_add->hd_pipe == -2)
			break ;
		heredoc.has_quote = 0;
	}
	return (all);
}
