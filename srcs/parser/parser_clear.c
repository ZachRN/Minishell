#include <structs.h>
#include <unistd.h>
#include <ft_split.h>
#include <stdlib.h>
#include <stdio.h>
t_parse *rm_one_from_parse_list(t_parse *to_remove)
{
	t_parse *to_return;

	if (!to_remove)
		return (NULL);
	to_return = to_remove->next;
	if (to_remove->cmd)
		free(to_remove->cmd);
	to_remove->cmd = NULL;
	if (to_remove->args)
		free_my_lines(to_remove->args);
	to_remove->args = NULL;
	if (to_remove->outfile)
		free(to_remove->outfile);
	to_remove->outfile = NULL;
	if (to_remove->infile)
		free(to_remove->infile);
	to_remove->infile = NULL;
	if (to_remove->heredoc_pipe > 0)
		close(to_remove->heredoc_pipe);
	free(to_remove);
	to_remove = NULL;
	return (to_return);
}

t_parse	*t_parse_clear_list(t_parse *head)
{
	if (!head)
		return (NULL);
	while (head)
		head = rm_one_from_parse_list(head);
	return (NULL);
}

t_parse	*list_malloc_error(t_parse *head)
{
	free(head);
	return (NULL);
}