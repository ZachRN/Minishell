#include <structs.h>
#include <stdio.h>
void lexer_display(t_lexer *head)
{
	t_lexer	*temp;

	if (!head)
		return ;
	temp = head;
	while (temp)
	{
		printf("Token #[%d]| Token Type: [%d]| Token Start-End: [%d] - [%d]",
			temp->token_id, temp->token_type, temp->start, temp->end);
		printf("| Token Content: [%s]\n", temp->content);
		temp = temp->next;
	}
	return ;
}