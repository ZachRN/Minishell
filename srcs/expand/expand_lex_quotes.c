/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_lex_quotes.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:50:11 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/13 13:48:34 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "lexer_all.h"
#include "utils.h"

static char	*quote_str_join(t_lexer *tail, char *input, char *str)
{
	char	*temp;
	char	*temp2;

	temp = str;
	temp2 = ft_substr(input, tail->prev->end + 1,
			tail->start - tail->prev->end - 1);
	str = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (str);
}

t_lexer	*rm_lex_quote_join(t_lexer *search, t_lexer *tail, char *str)
{
	t_lexer	*temp;

	temp = search->next;
	while (temp != tail)
		temp = rm_one_from_lexer_list(temp);
	search->end = temp->end;
	temp = rm_one_from_lexer_list(temp);
	free(search->content);
	search->content = str;
	search->next = temp;
	search->token_type = Expand;
	return (search);
}

t_lexer	*handle_lex_quotes(t_lexer *search, char *input)
{
	t_lexer	*tail;
	char	*str;
	char	*temp;
	int		quote_type;

	tail = search;
	quote_type = tail->token_type;
	str = ft_strdup("\0");
	tail = tail->next;
	while (tail && tail->token_type != quote_type)
	{
		if (tail->start - tail->prev->end > 1)
			str = quote_str_join(tail, input, str);
		temp = str;
		str = ft_strjoin(str, tail->content);
		free(temp);
		tail = tail->next;
	}
	search = rm_lex_quote_join(search, tail, str);
	return (search);
}

t_lexer	*handle_non_quote_join(t_lexer *search)
{
	t_lexer	*temp;
	char	*str_temp;

	temp = search->next;
	if (temp->token_type < Expand || search->token_type < Expand)
		return (temp);
	str_temp = search->content;
	search->content = ft_strjoin(search->content, temp->content);
	free(str_temp);
	search->end = temp->end;
	temp = rm_one_from_lexer_list(temp);
	search->next = temp;
	return (search);
}

/* The joing of quotes is a bit of a hassle Though the way it basically boils
down to it is that, It checks to make sure it is either a " ' $ or regular
expression, to join together. By checking if the start of next token entry
minus the end of the current token is equal to 1, meaning they are next to
each other within the regular string. Then copying the Content of the next one
into that of the current one, and removing the next one. The reason we
copy the content of the t_lexer and not from the string directly is because
we verifying to have the correct information incase of an expansion happening
earlier. It will also update the end of the token, to that of the deleted one
this is in case something after the deleted one must of also been joined.

This process is repeated for everything in the list until it gets to a pipe
character and then it stops.*/
t_lexer	*expand_lex_quotes(t_lexer *head, char *input)
{
	t_lexer	*search;

	if (!head)
		return (head);
	search = head;
	while (search && search->next && search->next->token_type != Pipe)
	{
		if (search->token_type == D_Quote || search->token_type == Quote)
			search = handle_lex_quotes(search, input);
		search = search->next;
	}
	search = head;
	while (search && search->next && search->next->token_type != Pipe)
	{
		if (search->next->start - search->end == 1)
			search = handle_non_quote_join(search);
		else
			search = search->next;
	}
	if (head->token_type >= Quote)
		head->token_type = Iden;
	return (head);
}
