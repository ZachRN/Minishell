/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_add_lex.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:49:09 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/14 12:37:01 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "utils.h"
#include "lexer_all.h"

static t_lexer	*new_lex(t_lexer *head, char *str)
{
	t_lexer	*to_add;

	to_add = (t_lexer *)malloc(sizeof(t_lexer));
	if (!to_add)
		exit(1);
	to_add->content = str;
	to_add->prev = NULL;
	to_add->next = NULL;
	to_add->start = head->start;
	to_add->end = head->end;
	to_add->token_id = head->token_id;
	to_add->token_type = Iden;
	if (to_add->next)
		to_add->next->prev = to_add;
	return (to_add);
}

static t_lexer	*add_lexer_after_one(t_lexer *head, t_lexer *new)
{
	if (!head)
		return (new);
	if (!new)
		return (head);
	new->next = head->next;
	new->prev = head;
	head->next = new;
	if (new->next)
		new->next->prev = new;
	return (new);
}

static t_lexer	*split_content(t_lexer *head)
{
	t_lexer	*save;
	t_lexer	*new;
	char	**content;
	int		i;

	content = ft_split(head->content, ' ');
	if (!content)
		return (head);
	if (!content[0] || !content[1])
	{
		free_my_lines(content);
		return (head);
	}
	i = 0;
	save = head;
	while (content[i])
	{
		new = new_lex(head, content[i]);
		head = add_lexer_after_one(head, new);
		i++;
	}
	save = rm_one_from_lexer_list(save);
	free(content);
	return (save);
}

t_lexer	*expand_add_lex(t_lexer *head, t_quote *check)
{
	t_lexer	*tail;
	int		first;

	if (!head)
		return (head);
	if (head->token_type != Expand)
		return (head);
	if (check->double_quote == -1)
		return (head);
	first = 0;
	tail = head;
	if (!tail->prev)
		first = 1;
	tail = split_content(tail);
	tail->token_type = Expand;
	return (tail);
}
