/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:35:00 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/13 13:31:14 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "handle_heredoc.h"
#include "expand_all.h"
#include "lexer_all.h"
#include "parser_all.h"
#include "utils.h"

t_together	*error_heredoc_clean(t_together *all, t_parse *to_add)
{
	all->last_error = 1;
	all->head = t_parse_clear_list(all->head);
	all->lex_head = t_lexer_clear_list(all->lex_head);
	t_parse_clear_list(to_add);
	return (all);
}

void	parse_display(t_parse *head)
{
	t_parse	*to_display;
	char	**temp;
	int		i;

	if (!head)
		return ;
	to_display = head;
	while (to_display)
	{
		temp = to_display->args;
		i = 0;
		printf("Command Name: [%s]\n", to_display->cmd);
		printf("Command Arguements: ");
		if (temp)
		{
			while (temp[i])
			{
				printf("[%s] ", temp[i]);
				i++;
			}
		}
		printf("\nOutfile: [%s]\nAppend: [%d]\nInfile: [%s]\n",
			to_display->outfile, to_display->append, to_display->infile);
		printf("Heredoc Pipe FD: [%d]\n", to_display->hd_pipe);
		printf("Type of Redirect: [%d]\n", to_display->rd_in);
		printf("Address of Next: [%p]\n", to_display->next);
		to_display = to_display->next;
	}
}

void	add_to_back(t_together *all, t_parse *to_add)
{
	t_parse	*temp;

	if (!all->head)
	{
		all->head = to_add;
		return ;
	}
	temp = all->head;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	return ;
}

int	find_last_in(t_lexer *head)
{
	t_lexer	*search;
	int		hold;

	search = head;
	hold = No_Infile;
	while (search && search->token_type != Pipe)
	{
		if (search->token_type == Lesser || search->token_type == Double_Lesser)
			hold = search->token_type;
		search = search->next;
	}
	if (hold == Double_Lesser)
		return (Heredoc);
	else if (hold == Lesser)
		return (Infile);
	return (No_Infile);
}

/*Welcome to the Parser, Here is the simple step by step of how it works 
These steps work in a loop until the lexer is empty
Step 1: Initalize the parser struct, parser/parser_init.c for more
Step 2: Handle Heredoc is the first thing we do for this set of commands
visit heredoc/heredoc_start.c for more info
Step 3: Expand the $ variables into their proper form!
visit expand/expansion_start.c for more info
Step 4: Join all the quotes and expanded variables together
visit expand/expand_lex_quotes.c for more info
Step 5: We then are going to handle all the redirections < << > >> next
visit parser/parser_redirections.c for mroe info
Step 6: Now all we have left is get the command name and arguements
Visit parser/parse_cmd_args.c for more info
Then we take all this information and pass it back to the main program for
the execution process*/

t_together	*parser(char *input, t_together *all)
{
	t_l_p_pack	pack;

	while (all->lex_head)
	{
		pack.no_file = 0;
		pack.to_add = parse_initalize();
		pack.to_add->rd_in = find_last_in(all->lex_head);
		all = handle_heredoc(input, all, &pack);
		if (pack.to_add->hd_pipe == -2)
			return (error_heredoc_clean(all, pack.to_add));
		all->lex_head = expansion_start(all, all->lex_head);
		all->lex_head = expand_lex_quotes(all->lex_head, input);
		pack.to_search = all->lex_head;
		pack = handle_redirections(pack);
		pack = cmd_args(pack);
		add_to_back(all, pack.to_add);
		if (pack.to_search)
			all->lex_head = pack.to_search;
		else
			all->lex_head = NULL;
	}
	parse_display(all->head);
	return (all);
}
