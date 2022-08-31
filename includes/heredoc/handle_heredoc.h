/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:18:47 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/31 13:21:45 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_HEREDOC_H
# define HANDLE_HEREDOC_H

# include <structs.h>

t_together	*handle_heredoc(char *input, t_together *all, t_l_p_pack *pack);

#endif