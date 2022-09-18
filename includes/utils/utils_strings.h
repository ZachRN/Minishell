/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:49:40 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:50:02 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_STRINGS_H
# define UTILS_STRINGS_H

int	compare_str(const char *str1, const char *str2);
int	check_word(const char *word, int word_len, const char *str);
int	compare_str_till_char(const char *env_name, const char *argument, char c);
int	find_char_in_str(char c, const char *str);

#endif /* utils_strings_h */
