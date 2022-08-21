/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_start.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:41:45 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/21 15:40:23 by znajda        ########   odam.nl         */
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
	int	prev_token;
}	t_quote;

static int	len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*handle_expand(char **env_array, char *str, int s_check, int heredoc)
{
	char	*temp;

	if (s_check == -1 || !env_array || !str || heredoc == Double_Lesser)
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

t_lexer	*expansion_loop(t_together *All, t_lexer *tail, t_quote *check)
{
	while (tail)
	{
		if (tail->token_type != Quote && tail->token_type != Double_Quote)
			check->prev_token = tail->token_type;
		if (tail->token_type == Expand)
			tail->content = handle_expand(All->env_array,
					tail->content, check->single_quote, check->prev_token);
		if (tail->token_type == Quote && check->double_quote == 1)
			check->single_quote *= -1;
		if (tail->token_type == Double_Quote && check->single_quote == 1)
			check->double_quote *= -1;
		tail = tail->next;
	}
}

t_lexer	*expansion_start(t_together *All, t_lexer *head)
{
	t_lexer	*tail;
	t_quote	check;

	check.double_quote = 1;
	check.single_quote = 1;
	tail = head->next;
	check.prev_token = head->token_type;
	if (head->token_type == Quote)
		check.single_quote *= -1;
	else if (head->token_type == Double_Quote)
		check.double_quote *= -1;
	else
		tail = head;
	expansion_loop(All, tail, &check);
	return (head);
}
