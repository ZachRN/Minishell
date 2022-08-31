/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_clear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:35:28 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/31 13:35:28 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <unistd.h>
#include <stdlib.h>

t_lexer	*rm_one_from_lexer_list(t_lexer *to_remove)
{
	t_lexer	*to_return;
	t_lexer	*prev;

	to_return = NULL;
	if (!to_remove)
		return (NULL);
	prev = to_remove->prev;
	to_return = to_remove->next;
	if (to_remove->content)
		free(to_remove->content);
	to_remove->content = NULL;
	if (to_remove)
		free(to_remove);
	to_remove = NULL;
	if (prev)
		prev->next = to_return;
	if (to_return)
		to_return->prev = prev;
	return (to_return);
}

t_lexer	*t_lexer_clear_list(t_lexer *head)
{
	if (!head)
		return (NULL);
	while (head)
		head = rm_one_from_lexer_list(head);
	return (NULL);
}
