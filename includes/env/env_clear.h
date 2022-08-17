/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clear.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:51:57 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/17 14:52:12 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_CLEAR_H
# define ENV_CLEAR_H

# include <structs.h>

void	env_clear(t_env *head);
t_parse	*list_malloc_error(t_parse *head);
t_env	*t_env_clear_list(t_env *head);
t_env	*t_env_remove_oldpwd(t_env *head);

#endif