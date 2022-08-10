/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 17:11:05 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/10 18:45:18 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <ft_strncmp.h>


t_env *rm_one_from_env_list(t_env *to_remove)
{
	t_env *to_return;

	if (!to_remove)
		return NULL;
	to_return = to_remove->next;
	if (to_remove->var_name)
		free(to_remove->var_name);
	if (to_remove->var_content)
		free(to_remove->var_content);
	if (to_remove->var_together)
		free(to_remove->var_together);
	free(to_remove);
	return (to_return);
}

t_env	*t_env_remove_oldpwd(t_env *head)
{
	t_env *temp;

	if (!head)
		return NULL;
	temp = head;
	while (temp)
	{
		if (ft_strncmp(temp->var_name, "OLDPWD", 6))
		{
			temp = rm_one_from_env_list(temp);
			break ;
		}
		temp = temp->next;
	}
}
