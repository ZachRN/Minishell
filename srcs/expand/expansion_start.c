/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_start.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:41:45 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/24 17:15:58 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <unistd.h>
#include <ft_strncmp.h>
#include <ft_strjoin.h>
#include <ft_strdup.h>
#include <ft_itoa.h>
#include <ft_strlen.h>

typedef struct s_quote
{
	int	double_quote;
	int	single_quote;
	int	prev_token;
}	t_quote;

char	*handle_dollar_sign(char *str, int last_code)
{
	free(str);
	if (!str[1])
		return (ft_strdup("$"));
	return (ft_itoa(last_code));
}

char	*handle_expand(char **env_array, char *str, int last_code)
{
	char	*temp;

	if (!env_array || !str)
		return (str);
	if (str[1] == '$' || !str[1])
		return (handle_dollar_sign(str, last_code));
	while (*env_array)
	{
		temp = ft_strjoin(str + 1, "=");
		if (!temp)
			return (str);
		if (ft_strncmp(*env_array, temp, ft_strlen(temp)) == 0)
			break ;
		free(temp);
		temp = NULL;
		env_array++;
	}
	free(str);
	str = NULL;
	if (temp)
		str = ft_strdup(*env_array + (ft_strlen(temp)));
	else
		str = ft_strdup("\0");
	free(temp);
	return (str);
}

void	expansion_loop(t_together *All, t_lexer *tail, t_quote *check)
{
	while (tail)
	{
		if (tail->token_type != Quote && tail->token_type != Double_Quote)
			check->prev_token = tail->token_type;
		if (tail->token_type == Expand && check->single_quote != -1)
			tail->content = handle_expand(All->env_array,
					tail->content, All->last_error);
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

	if (!head)
		return (NULL);
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
