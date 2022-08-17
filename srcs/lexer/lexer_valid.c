#include <structs.h>

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
		if ((previous_token < 6) && (to_search->token_type < 6))
			return (0);
		if (to_search->token_type == Quote && double_check == 1)
			single_check *= -1;
		if (to_search->token_type == Double_Quote && single_check == 1)
			double_check *= -1;
		previous_token = to_search->token_type;
		to_search = to_search->next;
	}
	if (double_check == -1 || single_check == -1 || (
		previous_token < Quote))
		return (0);
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
		return (0);
	else if (!to_search && (previous_token == Iden || previous_token == Expand))
		return (1);
	return (lexer_valid_loop(to_search, previous_token));
}