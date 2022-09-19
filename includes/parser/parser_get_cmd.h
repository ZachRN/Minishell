/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_get_cmd.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:48:17 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/19 14:02:29 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_GET_CMD_H
# define PARSER_GET_CMD_H

int		is_rel_abs_path(char *cmd);
char	*check_absolute_path(char *cmd);

#endif