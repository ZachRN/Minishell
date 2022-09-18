/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_start.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:21:14 by znajda            #+#    #+#             */
/*   Updated: 2022/09/18 12:52:36 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_START_H
# define EXPANSION_START_H

# include "structs.h"

t_lexer	*expansion_start(t_together *all, t_lexer *head);
char	*handle_expand(char **env_array, char *str, int last_code);

#endif
