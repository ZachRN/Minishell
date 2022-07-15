/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 15:37:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/07/15 16:26:46 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_strncmp.h>
#include <readline/readline.h>
#include <unistd.h>

int	minishell(void)
{
	char *input;
	int difference;
	
	while (TRUE)
	{
		input = readline("minishell>");
		if (!input)
			break;
		difference = ft_strncmp(input, "exit", 5);
		if (difference == FALSE)
			break ;
		if (input)
			free(input);
	}
	if (input)
		free(input);
	return (0);
}