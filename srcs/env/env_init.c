#include <structs.h>
#include <ft_strncmp.h>
#include <ft_split.h>
#include <ft_strdup.h>
#include <stdio.h>
#include <env_clear.h>


/*Set Specific Error Message here*/
void	t_env_add_back(t_env *head, t_env *to_add)
{
    t_env *loop_to_end;

    if (!head || !to_add)
        return ;
    loop_to_end = head;
    while (loop_to_end->next)
        loop_to_end = loop_to_end->next;
    loop_to_end->next = to_add;
    return ;
}

t_env   *t_env_create(char *str)
{
    t_env *to_create;
    char **split_str;

    if (!str)
        return NULL;
    to_create = (t_env *)malloc(sizeof(t_env));
    if (!to_create)
        return NULL;
    to_create->next = NULL;
    to_create->var_content = NULL;
    to_create->var_name = NULL;
    to_create->var_together = NULL;
    split_str = ft_split(str, '=');
    if (!split_str)
        return (to_create);
    to_create->var_name = ft_strdup(*split_str);
    to_create->var_content = ft_strdup(*(split_str + 1));
    to_create->var_together = ft_strdup(str);
    free_my_lines(split_str);
    return (to_create);
}

static t_env	*t_env_path_first(t_env *head)
{
	t_env	*to_search;
	t_env	to_hold;

	if (!head || ft_strncmp(head->var_name, "PATH", 5) == 0)
		return (head);
	to_search = head;
	while (to_search)
	{
		if (ft_strncmp(to_search->var_name, "PATH", 5) == 0)
			break ;
		to_search = to_search->next;
	}
	if (!to_search)
		return (head);
	to_hold.var_content = to_search->var_content;
	to_hold.var_name = to_search->var_name;
	to_hold.var_together = to_search->var_together;
	to_search->var_content = head->var_content;
	to_search->var_name = head->var_name;
	to_search->var_together = head->var_together;
	head->var_content = to_hold.var_content;
	head->var_name = to_hold.var_name;
	head->var_together = to_hold.var_together;
	return (head);
}
/*Set specific error message if malloc fails for list*/
t_env   *env_initalize(void)
{
    t_env *start;
    t_env *tail;
    extern char **environ;

    start = t_env_create(*environ);
    if (!start)
        return NULL;
    environ++;
    while (*environ)
    {
        tail = t_env_create(*environ);
        t_env_add_back(start, tail);
        environ++;
    }
    start = t_env_path_first(start);
	start = t_env_remove_oldpwd(start);
    return (start);
}