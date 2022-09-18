/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:50:08 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:50:26 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_WRITE_H
# define UTILS_WRITE_H

int	write_one_char_fd(int fd, char c);
int	write_str_fd(const char *str, int fd);

#endif /* utils_write_h */
