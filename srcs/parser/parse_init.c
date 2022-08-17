#include <structs.h>
#include <stdlib.h>

t_parse   *parse_initalize()
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
	head->heredoc = NULL;
	head->next = NULL;
	return (head);
}
