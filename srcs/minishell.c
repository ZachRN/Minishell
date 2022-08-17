/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 15:37:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/03 12:17:51 by znajda        ########   odam.nl         */
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

int	minishell(char **env_copy)
{
	char *input;
	int difference;
	t_parse *parse_vars;
	t_lexer *lex;

	while (TRUE)
	{
		input = readline("minishell>");
		if (!input)
			break;
		add_history(input);
		lex = lexer(input);
		lexer_display(lex);
		parse_vars = parser(input, env_copy);
		parse_vars = t_parse_clear_list(parse_vars);
		if (lexer_valid(lex))
			printf("This is a valid lexer!\n");
		else
			printf("Error: unepxected something\n");
		lex = t_lexer_clear_list(lex);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ; 
		free(input);
	}
	if (input)
		free(input);
	return (0);
}