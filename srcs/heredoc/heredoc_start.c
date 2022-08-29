#include <structs.h>
#include <ft_strncmp.h>
#include <ft_strdup.h>
#include <ft_substr.h>
#include <ft_strjoin.h>
#include <lexer_clear.h>
#include <lexer_display.h>
#include <stdio.h>
#include <heredoc_line_parse.h>
#include <signal_handles.h>

t_lexer *join_heredoc_quotes(t_lexer *head, t_heredoc *heredoc, char *input)
{
	t_lexer *tail;
	char	*temp;
	char	*temp_two;

	tail = head->next;
	heredoc->has_quote = 1;
	while(tail)
	{
		if (tail->token_type == Double_Quote || tail->token_type == Quote)
			break ;
		tail = tail->next;
	}
	temp = heredoc->End;
	temp_two = ft_substr(input, head->start + 1, tail->end - 1 - head->start);
	heredoc->End = ft_strjoin(temp, temp_two);
	free(temp);
	free(temp_two);
	return (tail);
}

t_lexer *remove_heredoc_list(t_lexer *head, t_lexer *tail)
{
	// t_lexer *temp;

	// temp = head->prev;
	while (head != tail)
		head = rm_one_from_lexer_list(head);
	head = rm_one_from_lexer_list(head);
	return (head);
	// if (temp)
	// {
	// 	if (head)
	// 		head->prev = temp;
	// 	temp->next = head;
	// 	return (temp);
	// }
	// else
	// {
	// 	if (head)
	// 	{
	// 		head->prev = NULL;
	// 		return (head);
	// 	}
	// 	return (NULL);
	// }
		
}
t_lexer	*go_handle(t_lexer *lex_head, t_heredoc *heredoc, char *input)
{
	t_lexer *tail;
	char	*temp;

	tail = lex_head->next;
	heredoc->End = ft_strdup("\0");
	while (tail)
	{
		if (tail->token_type == Double_Quote || tail->token_type == Quote)
			tail = join_heredoc_quotes(tail, heredoc, input);
		else
		{
			temp = heredoc->End;
			heredoc->End = ft_strjoin(heredoc->End, tail->content);
			free(temp);
		}
		if (tail->next && ((tail->next->start - tail->end != 1) || tail->next->token_type < Quote))
			break ;
		tail = tail->next;
	}
	return (remove_heredoc_list(lex_head, tail));
}

static int quick_fix(int token, t_together *All, t_lexer *tail)
{
	if (token == Double_Lesser)
	{
		All->lex_head = tail;
		if (tail)
			token = tail->token_type;
	}
	return (token);
}

t_together	*handle_heredoc(char *input, t_together *All, t_l_p_pack *pack)
{
	t_heredoc heredoc;
	t_lexer		*tail;
	int token;

	tail = All->lex_head;
	token = tail->token_type;
	heredoc.End = NULL;
	heredoc.has_quote = 0;
	while (tail)
	{
		if (tail->token_type == Double_Lesser)
		{
			tail = go_handle(tail, &heredoc, input);
			pack->to_add->heredoc_pipe = parse_line_heredoc(All, &heredoc, pack->to_add);
			signal_director(MAIN_SIG);
		}
		else if (tail)
			tail = tail->next;
		token = quick_fix(token, All, tail);
		if ((tail && tail->token_type == Pipe) || pack->to_add->heredoc_pipe == -2)
			break ;
		heredoc.has_quote = 0;
	}
	return (All);
}