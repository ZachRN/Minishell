/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:49:42 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/17 14:49:42 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CALLOC_H
# define FT_CALLOC_H

# include <stdlib.h>

/*Used to compare Strings to see if they are the same up to a certain point
currently being used to determine the path= variable*/
void	*ft_calloc(size_t nmeb, size_t size);

#endif