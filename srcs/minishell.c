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
#include <pwd.h>
#include <structs.h>
#include <parse_init.h>
#include <parse_clear.h>
int	minishell(t_env *head)
{
	char *input;
	int difference;
	t_parse *parse_vars;

	while (TRUE)
	{
		input = readline("minishell>");
		if (!input)
			break;
		add_history(input);
		parse_vars = parser(input, head);
		parse_vars = t_parse_clear_list(parse_vars);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ; 
		free(input);
	}
	if (input)
		free(input);
	return (0);
}