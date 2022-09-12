/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_start.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:41:45 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/12 15:18:42 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "structs.h"
#include "utils.h"
#include "expand_all.h"
#include "lexer_all.h"

char	*handle_dollar_sign(char *str, int last_code)
{
	free(str);
	if (!str[1])
		return (ft_strdup("$"));
	return (ft_itoa(last_code));
}

char	*handle_expand(char **env_array, char *str, int last_code)
{
	char	*temp;

	if (!env_array || !str)
		return (str);
	if (str[1] == '?' || !str[1])
		return (handle_dollar_sign(str, last_code));
	while (*env_array)
	{
		temp = ft_strjoin(str + 1, "=");
		if (!temp)
			return (str);
		if (ft_strncmp(*env_array, temp, ft_strlen(temp)) == 0)
			break ;
		free(temp);
		temp = NULL;
		env_array++;
	}
	free(str);
	str = NULL;
	if (temp)
		str = ft_strdup(*env_array + (ft_strlen(temp)));
	else
		str = ft_strdup("\0");
	free(temp);
	return (str);
}

t_lexer	*handle_first(t_lexer *head, t_lexer *tail, int first)
{
	if (first == 1)
		return (tail);
	else if (first == 0)
	{
		head->next = tail;
		return (head);
	}
	return (tail);
}

t_lexer	*expansion_loop(t_together *all, t_lexer *tail,
			t_quote *check, t_lexer *head)
{
	int	first;

	first = 0;
	if (head->token_type == Expand)
		first = 1;
	while (tail && tail->token_type != Pipe)
	{
		if (tail->token_type != Quote && tail->token_type != D_Quote)
			check->prev_token = tail->token_type;
		if (tail->token_type == Expand && check->single_quote != -1)
			tail->content = handle_expand(all->env_array,
					tail->content, all->last_error);
		tail = expand_add_lex(tail, check);
		if (first == 1)
			head = handle_first(head, tail, first);
		if (first == 1)
			first = 2;
		if (tail->token_type == Quote && check->double_quote == 1)
			check->single_quote *= -1;
		if (tail->token_type == D_Quote && check->single_quote == 1)
			check->double_quote *= -1;
		tail = tail->next;
	}
	return (head);
}

/*Expansion is a bit of a mess due to all the edge cases with it.
I will state the main issues that I faced while handling the code here.
Expansion works differently when it is within a "" and when it is outside of
them, I recommend testing them yourselves if you don't know them already.

Not expanding within '' and also taking into account when a " is within a '
or vice versa.
The expansion loop will look for variables with the $ start, and handle
them accordingly, edge case support for there being nothing after, to return
a $, $? to return the last error code, and $(STUFF) to account for the env
varible, returning ft_strdup("\0"); if it finds nothing.

It will change the content of the t_lexer from the $PATH to its new info
It will only expand until it inds a Pipe Token_Type, this is because we don't 
want to expand the next set of commands, incase heredoc does something with
that expansion in the next set. Visit heredoc if you wanna know why
*/
t_lexer	*expansion_start(t_together *all, t_lexer *head)
{
	t_quote	check;
	t_lexer	*tail;

	if (!head)
		return (NULL);
	check.double_quote = 1;
	check.single_quote = 1;
	check.prev_token = head->token_type;
	tail = head->next;
	if (head->token_type == Quote)
		check.single_quote *= -1;
	else if (head->token_type == D_Quote)
		check.double_quote *= -1;
	else
		tail = head;
	head = expansion_loop(all, tail, &check, head);
	return (head);
}
