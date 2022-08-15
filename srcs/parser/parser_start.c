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


//Temp is a temporary input just so that i am able to
//send yullia some semi functional code in the way
//that it will work

char **temp_duplicate(char **str)
{
	char **temp;
	int i;

	i = 0;
	if (!str)
		return (NULL);
	temp = str;
	while (temp[i])
		i++;
	temp = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (str[i])
	{
		temp[i] = ft_strdup(str[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

t_parse *parser(char *input, t_env *env)
{
    t_parse *head;
    t_parse *tail;
    char    **temp;

    head = parse_initalize();
	if (!head)
		return (NULL);
	// input_temp = ft_strdup(input);
    temp = ft_split(input, ' ');
    if (!temp)
        return (head);
	head->cmd = find_cmd_path(*temp, env);
	head->args = temp_duplicate(temp + 1);
	printf("Command Name/Path:%s\n", head->cmd);
	for (int i = 0; head->args[i]; i++)
		printf("Command args [%d]:%s\n", i, head->args[i]);
    free_my_lines(temp);
    return (head);
}