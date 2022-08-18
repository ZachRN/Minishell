/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_start.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:41:45 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/18 18:43:28 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <unistd.h>
#include <ft_strncmp.h>
#include <ft_strjoin.h>
#include <ft_strdup.h>

typedef struct s_quote
{
	int	double_quote;
	int	single_quote;
}	t_quote;

static int	len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*handle_expand(char **env_array, char *str, int single_check)
{
	char	*temp;

	if (single_check == -1 || !env_array || !str)
		return (str);
	while (*env_array)
	{
		temp = ft_strjoin(str + 1, "=");
		if (!temp)
			return (str);
		if (ft_strncmp(*env_array, temp, len(temp)) == 0)
			break ;
		free(temp);
		temp = NULL;
		env_array++;
	}
	if (str)
		free(str);
	if (temp)
		str = ft_strdup(*env_array + (len(temp)));
	else
		str = ft_strdup("\0");
	free(temp);
	return (str);
}

t_lexer	*expansion_start(t_together *All, t_lexer *head)
{
	t_lexer	*tail;
	t_quote	check;

	check.double_quote = 1;
	check.single_quote = 1;
	tail = head->next;
	if (head->token_type == Quote)
		check.single_quote *= -1;
	else if (head->token_type == Double_Quote)
		check.double_quote *= -1;
	else
		tail = head;
	while (tail)
	{
		if (tail->token_type == Expand)
			tail->content = handle_expand(All->env_array,
					tail->content, check.single_quote);
		if (tail->token_type == Quote && check.double_quote == 1)
			check.single_quote *= -1;
		if (tail->token_type == Double_Quote && check.single_quote == 1)
			check.double_quote *= -1;
		tail = tail->next;
	}
	return (head);
}
