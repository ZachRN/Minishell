/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_valid.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:42:52 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/19 13:07:33 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "structs.h"
#include "utils.h"

static int	print_error_message(char *str)
{
	write_str_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	write_str_fd(str, STDERR_FILENO);
	write_str_fd("'\n", STDERR_FILENO);
	return (0);
}

t_lexer	*check_change_iden(t_lexer *check, int single_check, int double_check)
{
	if (!check)
		return (check);
	if (single_check == -1)
	{
		if (check->token_type != Quote && check->token_type != Expand)
			check->token_type = Iden;
	}
	if (double_check == -1)
	{
		if (check->token_type != D_Quote && check->token_type != Expand)
			check->token_type = Iden;
	}
	return (check);
}

int	lexer_valid_loop(t_lexer *to_search, int previous_token)
{
	t_quote	check;

	check.double_quote = 1;
	check.single_quote = 1;
	if (previous_token == Quote && check.double_quote == 1)
		check.single_quote *= -1;
	else if (previous_token == D_Quote && check.single_quote == 1)
		check.double_quote *= -1;
	while (to_search)
	{
		check_change_iden(to_search, check.single_quote, check.double_quote);
		if ((previous_token < Pipe) && (to_search->token_type < Quote))
			return (print_error_message(to_search->content));
		if (to_search->token_type == Quote && check.double_quote == 1)
			check.single_quote *= -1;
		if (to_search->token_type == D_Quote && check.single_quote == 1)
			check.double_quote *= -1;
		previous_token = to_search->token_type;
		to_search = to_search->next;
	}
	if (check.double_quote == -1 || check.single_quote == -1)
		return (print_error_message("Unclosed double/quote"));
	else if (previous_token < Quote)
		return (print_error_message("newline"));
	return (1);
}

/*Welcome to the validity of the lexer. Basically all this is doing is checking
the order of the lexer, making sure everything can be in the place that it can
be in. Such as a < must be followed by " $ or a regular 'Identifier' string
It also checks to make sure that a " or a ' has a matching of the same to
end it, closing it. Not taking into account when it is within a different
pair of quotes. Such as "'" would be valid, where as ''" would not be

It will then also print out the correct error message in correspondence to
the type of error. Mostly a "Hey, error at this point" If you have
multiple errors in your command, only the first one is flagged before 
returning the prompt back to you. I would check out structs.h to see our Enum
if you are confusing by the random if statements numbers.*/

int	lexer_valid(t_lexer *head)
{
	t_lexer	*to_search;
	int		previous_token;

	if (!head)
		return (0);
	to_search = head;
	previous_token = to_search->token_type;
	to_search = to_search->next;
	if (previous_token == Pipe)
		return (print_error_message("|"));
	if (!to_search && (previous_token != Iden && previous_token != Expand))
		return (print_error_message("newline"));
	else if (!to_search && (previous_token == Iden || previous_token == Expand))
		return (1);
	return (lexer_valid_loop(to_search, previous_token));
}
