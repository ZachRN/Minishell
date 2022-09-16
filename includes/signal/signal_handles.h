/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handles.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:17:43 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/16 18:39:44 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLES_H
# define SIGNAL_HANDLES_H

# define MAIN_SIG 1
# define HEREDOC_SIG 2
# define PAUSE_SIG 3
# define DEFAULT_SIG 4
# define EXIT_INT 77

void	signal_director(int relocation);

#endif