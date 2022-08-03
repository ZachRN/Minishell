/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 15:37:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/07/20 14:06:43 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_strncmp.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <lexer.h>
#include <pwd.h>

void sighandler(int signum, siginfo_t *info, void *more_info)
{
	if (signum == SIGINT)
		write(1,"\nminishell>",11);
	// rl_on_new_line();
	signum++;
}

int	minishell(void)
{
	char *input;
	int difference;
	struct sigaction catch;

	catch.__sigaction_u.__sa_sigaction = sighandler;
	while (TRUE)
	{
		input = readline("minishell>");
		if (!input)
			break;
		difference = ft_strncmp(input, "exit", 5);
		if (difference == FALSE)
			break ;
		add_history(input);
		if (input)
			free(input);
	}
	if (input)
		free(input);
	ft_pwd();
	return (0);
}