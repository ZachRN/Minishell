#include <structs.h>
#include <ft_strncmp.h>


/*Set Specific Error Message here*/
void    *t_env_add_back(t_env *head, t_env *to_add)
{
    t_env *loop_to_end;

    if (!head || !to_add)
        return ;
    loop_to_end = head;
    while (loop_to_end->next)
        loop_to_end = loop_to_end->next;
    loop_to_end->next = to_add;
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
    to_create->var_content = ft_strdup(*split_str + 1);
    to_create->var_together = ft_strdup(str);
    return (to_create);
}

/*Set specific error message if malloc fails for list*/
t_env   *env_initalize(void)
{
    t_env *start;
    t_env *tail;
    extern char **env;

    start = t_env_create(*env);
    if (!start)
        return NULL;
    env++;
    while (*env)
    {
        tail = t_env_create(*env);
        t_env_add_back(start, tail);
        env++;
    }
    return (start);
}