#include <structs.h>
#include <parse_init.h>
#include <unistd.h>
#include <stdlib.h>
#include <ft_split.h>
#include <stdio.h>
#include <ft_strdup.h>
#include <ft_strncmp.h>
#include <parser_get_cmd.h>
#include <parse_clear.h>
#include <expansion_start.h>
#include <handle_heredoc.h>
#include <lexer_display.h>


//Temp is a temporary input just so that i am able to
//send yullia some semi functional code in the way
//that it will work

// char **temp_duplicate(char **str)
// {
// 	char **temp;
// 	int i;

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	while (temp[i])
// 		i++;
// 	temp = (char **)malloc((i + 1) * sizeof(char *));
// 	if (!temp)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		temp[i] = ft_strdup(str[i]);
// 		i++;
// 	}
// 	temp[i] = NULL;
// 	return (temp);
// }

t_together *parser(char *input, t_together *All)
{
    All->head = parse_initalize();
	if (!All->head || !All->lex_head)
		return (NULL);
	All = handle_heredoc(input, All);
	// lex_head = expansion_start(All, lex_head);
	lexer_display(All->lex_head);
    return (All);
}