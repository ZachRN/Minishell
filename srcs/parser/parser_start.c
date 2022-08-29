#include <structs.h>
#include <parse_init.h>
#include <unistd.h>
#include <stdlib.h>
#include <ft_split.h>
#include <stdio.h>
#include <ft_strdup.h>
#include <ft_strncmp.h>
#include <parser_get_cmd.h>
#include <parse_clear.h>
#include <expansion_start.h>
#include <handle_heredoc.h>
#include <lexer_display.h>
#include <expansion_add_lex.h>
#include <expand_lex_quotes.h>
#include <lexer_clear.h>
#include <parse_clear.h>
#include <parse_redirections.h>
#include <parse_cmd_args.h>

t_together *error_heredoc_clean(t_together *All, t_parse *to_add)
{
	All->last_error = 1;
	All->head = t_parse_clear_list(All->head);
	All->lex_head = t_lexer_clear_list(All->lex_head);
	t_parse_clear_list(to_add);
	return(All);
}

void	parse_display(t_parse *head)
{
	t_parse *to_display;
	char **temp;

	if (!head)
		return ;
	to_display = head;
	while (to_display)
	{
		temp = to_display->args;
		printf("-------------------------------------\n");
		printf("Command Name: [%s]\n", to_display->cmd);
		printf("Command Arguements: ");
		if (temp)
		{
			while (*temp)
			{
				printf("[%s] ", *temp);
				temp++;	
			}
		}
		printf("\nOutfile: [%s]\nAppend: [%d]\nInfile: [%s]\n",
			to_display->outfile, to_display->append, to_display->infile);
		printf("Heredoc Pipe FD: [%d]\n", to_display->heredoc_pipe);
		printf("Address of Next: [%p]\n", to_display->next);
		to_display = to_display->next;
	}
}

void	add_to_back(t_together *All, t_parse *to_add)
{
	t_parse	*temp;

	if (!All->head)
	{
		All->head = to_add;
		return ;
	}
	temp = All->head;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	return ;
}

t_together *parser(char *input, t_together *All)
{
	t_l_p_pack pack;
	
	All->lex_head = expansion_start(All, All->lex_head);
	All->lex_head = expand_lex_quotes(All->lex_head, input);
	while (All->lex_head)
	{
		pack.to_add	= parse_initalize();
		All = handle_heredoc(input, All, &pack);
		if (pack.to_add->heredoc_pipe == -2)
			return (error_heredoc_clean(All, pack.to_add));
		pack.to_search = All->lex_head;
		pack = handle_Redirections(pack);
		pack = cmd_args(pack);
		add_to_back(All, pack.to_add);
		if (pack.to_search)
			All->lex_head = pack.to_search;
		else
			All->lex_head = NULL;
	}
	parse_display(All->head);
    return (All);
}