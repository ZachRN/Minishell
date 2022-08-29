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

/*This is the core loop for our minishell to read an infinite amount
The step by step process is
Step 1: Check if the string exists, if it doesnt EOF was thrown and we exit
Step 2: Take the string and form it into a lexer, 
view lexer/lexer_init.c for more
Step 3: Next we make sure the lexer is valid and it can't be a incorrect
string that will be parsed, saving a headache for later. 
lexer/lexer_valid.c for more
Step 4: We then parse the lexer information, 
go to parser/parser_start.c for info on it
Step 5: We then execute based on the information that was parsed
Step 6: We do a basic clean up for the next round of commands.*/

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