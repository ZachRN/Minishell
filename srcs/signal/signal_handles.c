#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal_handles.h>

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

void	signal_director(int relocation)
{
	struct termios attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("Couldn't catch Sigquit Error");
	if (relocation == 1)
	{
		if (signal(SIGINT, signal_handle) == SIG_ERR)
			printf("Couldn't catch Sigint Error");
	}
	if (relocation == 2)
	{
		if (signal(SIGINT, heredoc_handle) == SIG_ERR)
			printf("Couldn't catch Sigint Error");
	}
	else if (relocation == 3)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			printf("Couldn't catch Sigint Error");
	}
}