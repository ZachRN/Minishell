/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_start.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:48:20 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/18 17:25:44 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_START_H
# define PARSER_START_H

# include <structs.h>

t_parse	*parser(char *input, t_together *All, t_lexer *head);

#endif