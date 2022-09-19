/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:48:14 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/17 14:52:21 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INIT_H
# define PARSE_INIT_H

# include "structs.h"

t_parse	*parse_initalize(void);
char	*check_if_need_to_free(t_l_p_pack pack);

#endif
