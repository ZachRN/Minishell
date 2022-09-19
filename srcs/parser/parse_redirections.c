/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:28:15 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/19 14:19:38 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "structs.h"
#include "lexer_all.h"
#include "utils.h"

t_l_p_pack	output_redirect(t_l_p_pack pack, int append)
{
	int	fd;

	pack.to_search = rm_one_from_lexer_list(pack.to_search);
	if (pack.to_add->outfile)
	{
		free(pack.to_add->outfile);
		pack.to_add->outfile = NULL;
	}
	pack.to_add->outfile = ft_strdup(pack.to_search->content);
	pack.to_search = rm_one_from_lexer_list(pack.to_search);
	if (pack.to_add->outfile[0] == '\0')
		pack.no_file = 2;
	if (append == 0)
		fd = open(pack.to_add->outfile, (O_TRUNC | O_CREAT | O_WRONLY), 0644);
	else
		fd = open(pack.to_add->outfile, (O_APPEND | O_CREAT | O_WRONLY), 0644);
	if (fd == -1)
	{
		while (pack.to_search && pack.to_search->token_type != Pipe)
			pack.to_search = rm_one_from_lexer_list(pack.to_search);
		pack.no_file = 1;
	}
	if (pack.to_add->outfile[0] == '\0')
		pack.no_file = 2;
	pack.to_add->append = append;
	close(fd);
	return (pack);
}

t_l_p_pack	input_redirect(t_l_p_pack pack)
{
	int		fd;
	t_lexer	*search;

	if (pack.to_add->infile)
	{
		free(pack.to_add->infile);
		pack.to_add->infile = NULL;
	}
	search = pack.to_search;
	search = rm_one_from_lexer_list(search);
	pack.to_add->infile = ft_strdup(search->content);
	search = rm_one_from_lexer_list(search);
	fd = open(pack.to_add->infile, O_RDONLY);
	if (fd == -1)
	{
		while (search && search->token_type != Pipe)
			search = rm_one_from_lexer_list(search);
		pack.no_file = 1;
	}
	if (pack.to_add->infile[0] == '\0')
		pack.no_file = 2;
	close(fd);
	pack.to_search = search;
	return (pack);
}

t_lexer	*find_first_none_direct(t_lexer *head)
{
	if (head->token_type > Lesser)
		return (head);
	head = head->next;
	while ((head->prev->token_type <= Lesser
			&& (head->next && head->next->token_type <= Lesser))
		|| head->token_type <= Lesser)
		head = head->next;
	if (head->prev->token_type <= Lesser)
		head = head->next;
	return (head);
}

/*Handling redirections isnt that much of an issue 
It checks for < > >> symbols and then takes the content of the token
following that one as the input for the name, this token as already been
expanded and joiend to form the correct information.

If the file does not exist for < it will mimic bash and scrap the rest
of the tokens for the command, as it does not execute the command at all
if the infile does not exist, and for > >> it will choose which is the
correct append mode for the command, and open them once to verify that they
exist and if not create them, only storing the most recent one. As that
is the only that bash writes to Though it will overwrite and delete
non append outfiles if they come earlier..*/

static t_lexer *to_remove_start(t_lexer *pack)
{
	t_lexer *search;

	search = pack;
	if (!search->prev)
		search = find_first_none_direct(search);
	else
		search = search->prev;
	return (search);
}

t_l_p_pack	handle_redirections(t_l_p_pack pack)
{
	t_lexer	*search;

	if (!pack.to_search)
		return (pack);
	search = to_remove_start(pack.to_search);
	pack.no_file = 0;
	while (pack.to_search && pack.to_search->token_type != Pipe)
	{
		if (pack.to_search->token_type == Greater)
			pack = output_redirect(pack, 0);
		else if (pack.to_search->token_type == Double_Greater)
			pack = output_redirect(pack, 1);
		else if (pack.to_search->token_type == Lesser)
			pack = input_redirect(pack);
		else if (pack.to_search)
			pack.to_search = pack.to_search->next;
		if (pack.no_file == 2)
			break ;
	}
	pack.to_search = search;
	return (pack);
}
