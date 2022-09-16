/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handles.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:26:47 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/16 18:40:42 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "signal_handles.h"

void	signal_handle(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_handle(int signo)
{
	if (signo == SIGINT)
		exit(EXIT_INT);
}

void	relocation_redirect(int relocation)
{
	if (relocation == 1)
	{
		if (signal(SIGINT, signal_handle) == SIG_ERR)
			write(STDERR_FILENO, "Couldn't catch Sigint Error\n", 28);
	}
	if (relocation == 2)
	{
		if (signal(SIGINT, heredoc_handle) == SIG_ERR)
			write(STDERR_FILENO, "Couldn't catch Sigint Error\n", 28);
	}
	else if (relocation == 3)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			write(STDERR_FILENO, "Couldn't catch Sigint Error\n", 28);
	}
	else if (relocation == 4)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	signal_director(int relocation)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	if (relocation == 4)
		attributes.c_lflag |= ECHOCTL;
	else
		attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		write(STDERR_FILENO, "Couldn't catch Sigquit Error\n", 29);
	relocation_redirect(relocation);
}
