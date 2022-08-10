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

static	void	check_leaks(void)
{
	system("leaks -quiet minishell");
}

int	main(void)
{
	t_env *env_vars;

	env_vars = env_initalize();
	atexit(check_leaks);
	return (minishell());
}
