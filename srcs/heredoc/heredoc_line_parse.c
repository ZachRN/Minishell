#include <structs.h>
#include <ft_itoa.h>
#include <unistd.h>
#include <ft_strncmp.h>
#include <ft_strlen.h>
#include <stdio.h>
#include <readline/readline.h>

char	*check_for_expansion(char *input, int has_quote)
{
		if (has_quote == 1)
			return (input);
		return (input);
}

void	write_input_to_pipe(char *pipe_eof, int has_quote, int pipe[2])
{
	char	*input;
	int a;

	a = pipe[0];
	while(1)
	{
		input = readline(">");
		if (!input)
			continue ;
		if (ft_strncmp(input, pipe_eof, ft_strlen(input) + 1) == 0)
			break ;
		input = check_for_expansion(input, has_quote);
		free(input);
	}
	free(input);
}
int	parse_line_heredoc(t_parse *head, t_heredoc *heredoc)
{
	int pipe_hold[2];

	if (pipe(pipe_hold) == -1)
		return (-2);
	write_input_to_pipe(heredoc->End, heredoc->has_quote, pipe_hold);
	close(pipe_hold[0]);
	close(pipe_hold[1]);
	head->heredoc_pipe = -1;
	free(heredoc->End);
	return (-2);
}