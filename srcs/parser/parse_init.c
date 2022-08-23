/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 17:55:24 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/17 17:55:36 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <stdlib.h>

t_parse	*parse_initalize(void)
{
	t_parse *head;

	head = (t_parse *)malloc(sizeof(t_parse));
	if (!head)
		return (NULL);
	head->cmd = NULL;
	head->args = NULL;
	head->outfile = NULL;
	head->append = -1;
	head->infile = NULL;
	head->heredoc_pipe = -1;
	head->next = NULL;
	return (head);
}
