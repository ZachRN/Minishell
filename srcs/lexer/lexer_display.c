/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_display.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:35:43 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/31 13:35:44 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <stdio.h>

void	lexer_display(t_lexer *head)
{
	t_lexer	*temp;

	if (!head)
		return ;
	temp = head;
	while (temp)
	{
		printf("Token #[%d]| Token Type: [%d]| Token Start-end: [%d] - [%d]",
			temp->token_id, temp->token_type, temp->start, temp->end);
		printf("| Token Content: [%s]\n", temp->content);
		temp = temp->next;
	}
	return ;
}
