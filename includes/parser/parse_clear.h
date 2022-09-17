/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_clear.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:48:10 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/17 15:34:42 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CLEAR_H
# define PARSE_CLEAR_H

# include "structs.h"

t_parse		*t_parse_clear_list(t_parse *head);
t_parse		*list_malloc_error(t_parse *head);
t_together	*clean_ambigious_file(t_together *all, t_l_p_pack pack);

#endif
