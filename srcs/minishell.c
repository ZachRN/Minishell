/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 15:15:16 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/17 16:03:34 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include "main.h"
#include "utils.h"
#include "structs.h"
#include "parser_all.h"
#include "lexer_all.h"
#include "cmd_loop.h"
#include "form_exec_struct.h"

//#include <lexer_display.h>
static void	control_d(void)
{
	printf("exit");
	exit(EXIT_SUCCESS);
}

void	clean_up_post_exec(t_exec exec, t_together *all, char *input)
{
	free(input);
	all->head = t_parse_clear_list(all->head);
	all->lex_head = t_lexer_clear_list(all->lex_head);
	if (exec.last_error != -10)
		all->last_error = exec.last_error;
	if (exec.upd_envp == NULL)
		return ;
	free_my_lines(all->env_array);
	all->env_array = exec.upd_envp;
	exec.upd_envp = NULL;
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

int	minishell(t_together *all)
{
	char	*input;
	t_exec	exec;

	exec.upd_envp = NULL;
	while (TRUE)
	{
		exec.last_error = -10;
		input = readline("minishell>");
		if (!input)
			control_d();
		add_history(input);
		all->lex_head = lexer(input);
		if (lexer_valid(all->lex_head))
			all = parser(input, all);
		else if (input[0] != '\0')
			all->last_error = 258;
		if (all->head)
			exec = creat_exec_loop_commands(all, all->env_array);
		clean_up_post_exec(exec, all, input);
	}
	if (input)
		free(input);
	return (0);
}
