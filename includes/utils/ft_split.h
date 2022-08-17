/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:49:36 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/17 14:49:36 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPLIT_H
# define FT_SPLIT_H

/*Used to split a variable into seperate strings, used for finding the path in
this program*/
char	**ft_split(char const *s, char c);
char	**free_my_lines(char **str);

#endif