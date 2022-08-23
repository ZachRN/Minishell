/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 17:11:05 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/23 15:38:10 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <ft_strncmp.h>
#include <stdio.h>
/*Legacy code!*/

t_env *rm_one_from_env_list(t_env *to_remove)
{
	t_env *to_return;

	to_return = NULL;
	if (!to_remove)
		return NULL;
	if (to_remove->next)
		to_return = to_remove->next;
	if (to_remove->var_name)
		free(to_remove->var_name);
	to_remove->var_name = NULL;
	if (to_remove->var_content)
		free(to_remove->var_content);
	to_remove->var_content = NULL;
	if (to_remove->var_together)
		free(to_remove->var_together);
	to_remove->var_together = NULL;
	if (to_remove)
		free(to_remove);
	to_remove = NULL;
	return (to_return);
}

t_env	*t_env_clear_list(t_env *head)
{
	if (!head)
		return (NULL);
	while (head)
		head = rm_one_from_env_list(head);
	return (head);

}
t_env	*t_env_remove_oldpwd(t_env *head)
{
	t_env *to_search;
	t_env *temp;

	if (!head)
		return (head);
	to_search = head;
	if (ft_strncmp(to_search->var_name, "OLDPWD", 7) == 0)
		return (rm_one_from_env_list(head));
	temp = head;
	while (to_search)
	{
		if (ft_strncmp(to_search->var_name, "OLDPWD", 7) == 0)
		{
			//printf("%s\n", temp->var_name);
			temp->next = rm_one_from_env_list(to_search);
			break ;
		}
		temp = to_search;
		to_search = to_search->next;
	}
	return (head);
}
