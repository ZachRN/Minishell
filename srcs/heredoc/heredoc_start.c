#include <structs.h>
#include <ft_strncmp.h>

t_lexer	*heredoc_quotejoin(t_lexer *tail, char **str)
{
	char *temp;

	if (tail->next->token_type == tail->token_type)
		return free
}

t_lexer	*figure_out_eof(t_lexer *head, char **str)
{
	t_lexer *tail;
	char *temp;

	if (head->token_type != Quote || head->token_type != Double_Quote)
		*str = ft_strdup(head->content);
	else
		*str = ft_strdup("\0");
	tail = head;
	while (tail)
	{
		temp = *str;
		if (tail->token_type == Quote || tail->token_type == Double_Quote)
			tail = heredoc_quotejoin(tail, str);
		if (!tail->next)
			break ;
		if (tail->token_type < Quote || tail->end + 1 != tail->next->start)
			break ;
		else if (tail->next->token_type != Quote ||
				tail->next->token_type != Double_Quote)
			ft_strjoin(*str, tail->next->content);
		free(temp);
		tail = tail->next;
	}
	return (head);
}

t_lexer	*handle_heredoc(t_lexer *lex_head, t_parse *head)
{
	t_lexer	*tail;
	char	*eof;
	int		counter;

	counter = 0;
	tail = lex_head;
	while (tail->next)
	{
		if (tail->next->token_type == Double_Lesser)
		{
			tail->next = figure_out_eof(tail->next, eof);
			// tail = ();
		}
		else if (tail->next->token_type == Pipe)
			break ;
		tail = tail->next;
	}
}