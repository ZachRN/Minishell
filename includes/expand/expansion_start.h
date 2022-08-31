/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_start.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 17:21:14 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/31 13:21:45 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_START_H
# define EXPANSION_START_H

# include <structs.h>

t_lexer	*expansion_start(t_together *all, t_lexer *head);
char	*handle_expand(char **env_array, char *str, int last_code);

#endif