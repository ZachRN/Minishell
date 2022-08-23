/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 14:59:17 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/23 18:22:42 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <stdlib.h>
#include <minishell.h>
#include <structs.h>
// #include <env_display.h>
// #include <env_init.h>
// #include <env_clear.h>
#include <env_copy.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <unistd.h>

int g_signal_status = 0;
struct termios saved;

void	signal_handle(int signo)
{
	if (signo == SIGINT && g_signal_status == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		
	}
}

static	void	check_leaks(void)
{
	system("leaks -quiet minishell");
	// tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}

int	main(int argc, char *argv[], char *env[])
{
	t_together All;
	tcgetattr(STDIN_FILENO, &saved);
	struct termios attributes;
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);

	(void)argc;
	(void)argv;
	All.env_array = env_copy(env);
	All.last_error = -1;
	All.head = NULL;
	atexit(check_leaks);
	if (signal(SIGINT, signal_handle) == SIG_ERR)
		printf("Couldn't Catch Sigint Error");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("Couldn't Catch Sigquit error");
	env_vars_copy_display(All.env_array);
	minishell(&All);
	free_lines(All.env_array);
	exit(1);
}
