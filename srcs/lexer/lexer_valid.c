#include <structs.h>
#include <stdio.h>

static int	print_error_message(char *str)
{
	printf("minishell: syntax error near unexpected token '%s'\n", str);
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
		if (check->token_type != Double_Quote && check->token_type != Expand)
			check->token_type = Iden;
	}
	return (check);
}
int lexer_valid_loop(t_lexer *to_search, int previous_token)
{
	int single_check;
	int double_check;

	double_check = 1;
	single_check = 1;
	if (previous_token == Quote && double_check == 1)
		single_check *= -1;
	else if (previous_token == Double_Quote && single_check == 1)
		double_check *= -1;
	while (to_search)
	{
		check_change_iden(to_search, single_check, double_check);
		if ((previous_token < 6) && (to_search->token_type < 6))
			return (print_error_message(to_search->content));
		if (to_search->token_type == Quote && double_check == 1)
			single_check *= -1;
		if (to_search->token_type == Double_Quote && single_check == 1)
			double_check *= -1;
		previous_token = to_search->token_type;
		to_search = to_search->next;
	}
	if (double_check == -1 || single_check == -1)
		return (print_error_message("Unclosed double/quote"));
	else if (previous_token < Quote)
		return (print_error_message("newline"));
	return (1);
}

int	lexer_valid(t_lexer *head)
{
	t_lexer *to_search;
	int previous_token;

	if (!head)
		return (0);
	to_search = head;
	previous_token = to_search->token_type;
	to_search = to_search->next;
	if (!to_search && (previous_token != Iden && previous_token != Expand))
		return (print_error_message("newline"));
	else if (!to_search && (previous_token == Iden || previous_token == Expand))
		return (1);
	return (lexer_valid_loop(to_search, previous_token));
}