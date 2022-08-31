/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_line_parse.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:18:40 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/31 13:21:45 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_LINE_PARSE_H
# define HEREDOC_LINE_PARSE_H

# include <structs.h>

int	parse_line_heredoc(t_together *all, t_heredoc *heredoc, t_parse *to_add);

#endif