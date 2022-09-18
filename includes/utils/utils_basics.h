/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basics.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:48:34 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:49:04 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BASICS_H
# define UTILS_BASICS_H

typedef enum e_status
{
	FLS = 0,
	TRU = 1,
	ERR = -1
}			t_status;

int	string_len(const char *str);
int	strlen_till_char(char *str, char c);
int	find_arr_len(char **arr);
int	is_char(char c);
int	is_number(char c);

#endif /* utils_basics_h */
