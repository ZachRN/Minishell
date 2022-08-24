#include <structs.h>
#include <stdio.h>
#include <ft_itoa.h>
#include <unistd.h>
#include <ft_strncmp.h>
#include <ft_strlen.h>
#include <readline/readline.h>
#include <signal_handles.h>
#include <ft_substr.h>
#include <ft_strjoin.h>
#include <expansion_start.h>

int		found_dollar(char *input, int i, t_together *All)
{
	char *temp;
	char *temp2;
	int j;

	j = i;
	temp = ft_substr(input, 0, i);
	if (!temp)
		return (-1);
	while (input[j] && input[j] != ' ' && input[j] != '$')
		j++;
	printf("%s\n", temp);
	temp2 = ft_substr(input, i, j);
	printf("%s\n",temp2);
	free(temp);
	free (temp2);
	return (j);	
}
char	*check_for_expansion(char *input, int has_quote, t_together *All)
{
	int	i;

	i = 0;
	if (has_quote == 1)
		return (input);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i = found_dollar(input, i, All);
			if (i == -1)
				break ;
		}
		i++;
	}
	return (input);
}

void	write_input_to_pipe(char *pipe_eof, int has_quote, int pipe_hold[2], t_together *All)
{
	char	*input;

	signal_director(HEREDOC_SIG);
	while(1)
	{
		input = readline(">");
		if (!input)
			break ;
		if (ft_strncmp(input, pipe_eof, ft_strlen(input) + 1) == 0)
			break ;
		input = check_for_expansion(input, has_quote, All);
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
	}
	free(input);
	exit(EXIT_SUCCESS);
}

int	parse_line_heredoc(t_together *All, t_heredoc *heredoc)
{
	int pipe_hold[2];
	int status;
	int	p_id;
	int ex;

	ex = -2;
	if (pipe(pipe_hold) == -1)
		return (-2);
	signal_director(PAUSE_SIG);
	p_id = fork();
	if (p_id == -1)
		return (-2);
	else if (p_id == 0)
		write_input_to_pipe(heredoc->End, heredoc->has_quote, pipe_hold, All);
	close(pipe_hold[1]);
	waitpid(p_id, &status, 0);
	if (WIFEXITED(status))
		ex = WEXITSTATUS(status);
	if (ex == -2)
		return (-2);
	free(heredoc->End);
	heredoc->End = NULL;
	return (0);
}