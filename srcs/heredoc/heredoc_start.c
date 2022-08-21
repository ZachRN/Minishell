#include <structs.h>
#include <ft_strncmp.h>
#include <ft_strdup.h>
#include <ft_substr.h>
#include <ft_strjoin.h>
#include <lexer_clear.h>
#include <lexer_display.h>
#include <stdio.h>

typedef struct s_heredoc
{
	int		has_quote;
	char	*End;
	int		pipe_number;
	int		heredoc_counter;
}				t_heredoc;


void	init_heredoc_struct(t_heredoc *heredoc)
{
	heredoc->End = NULL;
	heredoc->has_quote = 0;
}

t_lexer *join_heredoc_quotes(t_lexer *head, t_heredoc *heredoc, char *input)
{
	t_lexer *tail;
	char	*temp;
	char	*temp_two;

	tail = head->next;
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
	t_lexer *temp;

	temp = head->prev;
	while (head != tail)
		head = rm_one_from_lexer_list(head);
	head = rm_one_from_lexer_list(head);
	if (temp)
	{
		temp->next = head;
		return (temp);
	}
	else
		return (tail);
		
}
t_lexer	*go_handle(t_lexer *lex_head, t_parse *head, t_heredoc *heredoc, char *input)
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
		if (!tail->next || (tail->next->start - tail->end != 1))
			break ;
		tail = tail->next;
	}
	printf("heredoc End: %s\n", heredoc->End);
	free(heredoc->End);
	lex_head = remove_heredoc_list(lex_head, tail);
	return (lex_head);
}

t_parse	*handle_heredoc(t_lexer **lex_head, t_parse *head, char *input)
{
	t_lexer	*tail;
	t_lexer *hold;
	t_heredoc heredoc;

	tail = *lex_head;
	hold = *lex_head;
	init_heredoc_struct(&heredoc);
	heredoc.pipe_number = 0;
	heredoc.pipe_number = 0;
	while (tail)
	{
		if (tail->token_type == Double_Lesser)
			tail = go_handle(tail, head, &heredoc, input);
		else if (tail->token_type == Pipe)
			break ;
		if (tail)
			tail = tail->next;
	}
	*lex_head = hold;
	return (head);
}