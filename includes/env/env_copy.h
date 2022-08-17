/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_copy.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:51:02 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/17 14:52:41 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_COPY_H
# define ENV_COPY_H

int		get_size_of_env(char **env);
char	**copy_env_list(char **to_return, char **env);
char	**free_lines(char **str);
void	env_vars_copy_display(char **str);
char	**env_copy(char **env);

#endif