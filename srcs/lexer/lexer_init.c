#include <structs.h>
#include <stdlib.h>
#include <ft_substr.h>
#include <stdio.h>

int	determine_token(char *input, int pos)
{
	if (input[pos] == '<' && input[pos + 1] == '<')
		return (Double_Lesser);
	if (input[pos] == '<')
		return (Lesser);
	if (input[pos] == '>' && input[pos + 1] == '>')
		return (Double_Greater);
	if (input[pos] == '>')
		return (Greater);
	if (input[pos] == '|')
		return (Pipe);
	if (input[pos] == '"')
		return (Double_Quote);
	if (input[pos] == '\'')
		return (Quote);
	if (input[pos] == '$')
		return (Expand);
	return (Iden);
}

int	find_end_of_iden(char *input, int pos)
{
	while (input[pos])
	{
		if (input[pos] == '<' || input[pos] == '>' || input[pos] == '|' ||
			input[pos] == '$' || input[pos] == '\'' || input[pos] == '"' ||
			input[pos] == ' ' || (input[pos] >= 9 && input[pos] <= 13))
			return (pos - 1);
		pos++;
	}
	return (pos - 1);
}

t_lexer *create_new_lexer(char *input, int *pos, int token_id)
{
	t_lexer *temp;
	int		token;
	int		end_pos;

	temp = (t_lexer *)malloc(sizeof(t_lexer));
	if (!temp)
		return (NULL);
	token = determine_token(input, *pos);
	if (token == Lesser || token == Greater || token == Pipe ||
		token == Quote || token == Double_Quote)
		end_pos = *pos;
	else if (token == Double_Lesser || token == Double_Greater)
		end_pos = *pos + 1;
	else
		end_pos = find_end_of_iden(input, *pos + 1);
	temp->next = NULL;
	temp->prev = NULL;
	temp->start = *pos;
	temp->end = end_pos;
	temp->token_type = token;
	temp->token_id = token_id;
	temp->content = ft_substr(input, *pos, end_pos - *pos + 1);
	*pos = end_pos;
	return (temp);
}

void	add_lexer_to_end(t_lexer *head, t_lexer *tail)
{
	t_lexer	*temp;
	t_lexer *temp_prev;

	if (!tail)
		return ;
	temp = head;
	temp_prev = head;
	while (temp->next)
	{
		temp = temp->next;
		if (!temp->next)
			break ;
		temp_prev = temp_prev->next;
	}
	temp->next = tail;
	if (temp == head)
		return ;
	temp->prev = temp_prev;
	return ;
}

t_lexer *lexer(char *input)
{
	int 	pos;
	int		token_id;
	t_lexer *head;
	t_lexer *tail;

	head = NULL;
	tail = NULL;
	token_id = 0;
	pos = 0;
	while(input[pos])
	{
		while (input[pos] == 32 || (input[pos] >= 9 && input[pos] <= 13))
			pos++;
		if (!input[pos])
			break ;
		if (!head)
			head = create_new_lexer(input, &pos, token_id);
		else
			tail = create_new_lexer(input, &pos, token_id);
		token_id++;
		if (head)
			add_lexer_to_end(head, tail);
		pos++;
	}
	return (head);
}