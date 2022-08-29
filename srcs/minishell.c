/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 15:37:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/24 16:40:10 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_strncmp.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <parser_start.h>
#include <structs.h>
#include <parse_init.h>
#include <parse_clear.h>
#include <lexer.h>
#include <lexer_clear.h>
#include <lexer_valid.h>

static void control_d()
{
	printf("exit");
	exit(EXIT_SUCCESS);
}

int	minishell(t_together *All)
{
	char *input;

	while (TRUE)
	{
		input = readline("minishell>");
		if (!input)
			control_d();
		add_history(input);
		All->lex_head = lexer(input);
		if (lexer_valid(All->lex_head))
			All = parser(input, All);
		else
			All->last_error = 258;
		//YOU CAN PUT YOUR FUNCTION HERE
		//All is a t_together struct, , where ->head
		// is the most important one for you, it contains
		//the struct that holds the cmd name, arguements, outfile
		//etc etc.. last_Error is also somehting that potentially needs to be updated
		//from you with the exit code of the last command.

		//Important to know that during execution you need to check for the path
		//of the command name.
		//Also check if the infile exists, if it doesnt exist you should void
		//the entire command basically. I can explain in more detail if you want.
		All->head = t_parse_clear_list(All->head);
		All->lex_head = t_lexer_clear_list(All->lex_head);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ; 
		free(input);
	}
	if (input)
		free(input);
	return (0);	
}