/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 15:14:29 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/12 15:14:33 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>
#include "minishell.h"
#include "structs.h"
#include "env_copy.h"
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include "signal_handles.h"

/* We start the project by making a copy of the environmental variables passed
to us, as well as a set up for the primary of storing information with our
struct called a t_together which just holds different variables.
Minishell.c holds our infinite while loop and the post set up information. 
This also sets up the start of our signals to ingore SIG_INT and SIG_QUIT
Control + C && Control + \ */

int	main(int argc, char *argv[], char *env[])
{
	t_together	all;

	(void)argc;
	(void)argv;
	all.env_array = env_copy(env);
	all.last_error = 0;
	all.head = NULL;
	all.lex_head = NULL;
	signal_director(1);
	minishell(&all);
	free_lines(all.env_array);
	exit(1);
}