/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_clear.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:50:26 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/21 17:28:19 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_CLEAR_H
# define LEXER_CLEAR_H

# include <structs.h>

t_lexer	*t_lexer_clear_list(t_lexer *head);
t_lexer *rm_one_from_lexer_list(t_lexer *to_remove);

#endif