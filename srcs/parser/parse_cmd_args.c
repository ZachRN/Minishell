#include <structs.h>
#include <ft_strdup.h>
#include <stdlib.h>
#include <ft_split.h>
#include <lexer_clear.h>

#include <stdio.h>
#include <lexer_display.h>

char	**make_arg_list(t_l_p_pack pack, int i)
{
	char **temp;
	t_lexer *search;

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

t_l_p_pack cmd_args(t_l_p_pack pack)
{
	t_lexer *search;
	char **temp;
	int	i;

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