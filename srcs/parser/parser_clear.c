/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:29:59 by znajda            #+#    #+#             */
/*   Updated: 2022/09/18 11:56:40 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"
#include "parser_all.h"
#include "lexer_all.h"

//split rm_one_from_parse_list function
void	free_cmd_args_outfile_infile(t_parse *to_remove)
{
	if (to_remove->cmd)
		free(to_remove->cmd);
	to_remove->cmd = NULL;
	if (to_remove->args)
		free_my_lines(to_remove->args);
	to_remove->args = NULL;
	if (to_remove->outfile)
		free(to_remove->outfile);
	to_remove->outfile = NULL;
	if (to_remove->infile)
		free(to_remove->infile);
	to_remove->infile = NULL;
}

t_parse	*rm_one_from_parse_list(t_parse *to_remove)
{
	t_parse	*to_return;

	if (!to_remove)
		return (NULL);
	to_return = to_remove->next;
	free_cmd_args_outfile_infile(to_remove);
	if (to_remove->heredoc)
	{
		unlink(to_remove->heredoc);
		free(to_remove->heredoc);
	}
	to_remove->heredoc = NULL;
	free(to_remove);
	to_remove = NULL;
	return (to_return);
}

t_parse	*t_parse_clear_list(t_parse *head)
{
	if (!head)
		return (NULL);
	while (head)
		head = rm_one_from_parse_list(head);
	return (NULL);
}

t_together	*clean_ambigious_file(t_together *all, t_l_p_pack pack)
{
	all->lex_head = t_lexer_clear_list(all->lex_head);
	write_str_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
	add_to_back(all, pack.to_add);
	all->head = t_parse_clear_list(all->head);
	all->last_error = 1;
	return (all);
}
