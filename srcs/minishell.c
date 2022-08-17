/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 15:37:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/17 17:56:09 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_strncmp.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <parser_start.h>
#include <structs.h>
#include <parse_init.h>
#include <parse_clear.h>
#include <lexer.h>
#include <lexer_clear.h>
#include <lexer_display.h>
#include <lexer_valid.h>

int	minishell(t_together *All)
{
	char *input;
	t_lexer *lex;

	while (TRUE)
	{
		input = readline("minishell>");
		if (!input)
			break;
		add_history(input);
		lex = lexer(input);
		lexer_display(lex);
		All->head = parser(input, All->env_array);
		if (lexer_valid(lex))
			printf("This is a valid lexer!\n");
		else
			printf("Error: something\n");
		All->head = t_parse_clear_list(All->head);
		lex = t_lexer_clear_list(lex);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ; 
		free(input);
	}
	if (input)
		free(input);
	return (0);
}