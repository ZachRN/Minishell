/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 14:59:17 by znajda        #+#    #+#                 */
/*   Updated: 2022/07/15 15:57:57 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <stdlib.h>
#include <minishell.h>
#include <structs.h>
#include <env_display.h>
#include <env_init.h>
#include <env_clear.h>

static	void	check_leaks(void)
{
	system("leaks -quiet minishell");
}

int	main(void)
{
	t_env *env_vars;

	env_vars = env_initalize();
	atexit(check_leaks);
	env_display(env_vars);
	minishell(env_vars);
	t_env_clear_list(env_vars);
	exit(1);
}
