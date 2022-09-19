/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_line_parse.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: yuliia <yuliia@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:45:02 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/19 14:16:09 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <fcntl.h>
#include "structs.h"
#include "utils.h"
#include "signal_handles.h"
#include "expand_all.h"

t_pack	found_dollar(t_pack pack, t_together *all)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		j;

	j = pack.i + 1;
	if (pack.i == 0)
		temp = ft_strdup("\0");
	else
		temp = ft_substr(pack.str, 0, pack.i);
	while (pack.str[j] && pack.str[j] != ' ' && pack.str[j] != '$')
		j++;
	temp2 = ft_substr(pack.str, pack.i, j);
	temp2 = handle_expand(all->env_array, temp2, all->last_error);
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	temp = ft_substr(pack.str, j, ft_strlen(pack.str));
	pack.i = ft_strlen(temp);
	free(pack.str);
	pack.str = ft_strjoin(temp3, temp);
	free(temp3);
	free(temp);
	free(temp2);
	return (pack);
}

char	*check_for_expansion(char *input, int has_quote, t_together *all)
{
	t_pack	pack;

	pack.i = 0;
	pack.str = input;
	if (has_quote == 1)
		return (input);
	while (pack.str[pack.i])
	{
		if (pack.str[pack.i] == '$')
		{
			pack = found_dollar(pack, all);
			if (pack.i == -1 || !pack.str
				|| (pack.str && pack.i >= ft_strlen(pack.str)))
				break ;
		}
		pack.i++;
	}
	return (pack.str);
}

void	write_input_to_pipe(char *pipe_eof, int has_quote,
			t_parse *to_add, t_together *all)
{
	char	*input;
	int		fd;

	fd = open(to_add->heredoc, (O_WRONLY | O_TRUNC | O_CREAT), 0644);
	if (fd < 0)
		exit(EXIT_INT);
	signal_director(HEREDOC_SIG);
	while (1)
	{
		input = readline(">");
		if (!input)
			break ;
		if (ft_strncmp(input, pipe_eof, ft_strlen(input) + 1) == 0)
			break ;
		input = check_for_expansion(input, has_quote, all);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	exit(EXIT_SUCCESS);
}

char	*heredoc_str(t_together *all)
{
	int		counter;
	char	*str;
	char	*itoa;
	t_parse	*search;

	search = all->head;
	counter = 0;
	if (search)
	{
		while (search)
		{
			search = search->next;
			counter++;
		}
	}
	itoa = ft_itoa(counter);
	str = ft_strjoin(".heredoc", itoa);
	free(itoa);
	return (str);
}

int	parse_line_heredoc(t_together *all, t_heredoc *heredoc, t_parse *to_add)
{
	int	status;
	int	p_id;
	int	ex;

	ex = -2;
	if (to_add->heredoc)
		free(to_add->heredoc);
	to_add->heredoc = heredoc_str(all);
	signal_director(PAUSE_SIG);
	p_id = fork();
	if (p_id == -1)
		return (-2);
	else if (p_id == 0)
		write_input_to_pipe(heredoc->end, heredoc->has_quote, to_add, all);
	waitpid(p_id, &status, 0);
	free(heredoc->end);
	heredoc->end = NULL;
	if (WIFEXITED(status))
		ex = WEXITSTATUS(status);
	if (ex == EXIT_INT)
		return (ex);
	return (0);
}
