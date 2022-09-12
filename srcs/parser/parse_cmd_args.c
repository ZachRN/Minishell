/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd_args.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:27:25 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/12 15:16:32 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"
#include "utils.h"
#include "lexer_all.h"

char	**make_arg_list(t_l_p_pack pack, int i)
{
	char	**temp;
	t_lexer	*search;

	temp = (char **)malloc((i + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	temp[i] = NULL;
	search = pack.to_search;
	i = 0;
	while (search && search->token_type != Pipe)
	{
		temp[i] = ft_strdup(search->content);
		if (!temp)
			return (free_my_lines(temp));
		search = search->next;
		i++;
	}
	return (temp);
}

/*The last step of the parser is to grab the command name and arguements
the first command in the list at this point must be the command
after that we set args to equal to a **str with each element set to the
remaining tokens left in the list until its done or until a pipe token.*/
t_l_p_pack	cmd_args(t_l_p_pack pack)
{
	t_lexer	*search;
	char	**temp;
	int		i;

	if (!pack.to_search)
		return (pack);
	search = pack.to_search;
	pack.to_add->cmd = ft_strdup(search->content);
	i = 0;
	while (search && search->token_type != Pipe)
	{
		search = search->next;
		i++;
	}
	pack.to_add->args = make_arg_list(pack, i);
	temp = pack.to_add->args;
	while (pack.to_search && pack.to_search->token_type != Pipe)
		pack.to_search = rm_one_from_lexer_list(pack.to_search);
	pack.to_search = rm_one_from_lexer_list(pack.to_search);
	return (pack);
}
