//
//  utils_strings.h
//  x_mini
//
//  Created by Julia Demura on 06/09/2022.
//

#ifndef utils_strings_h
#define utils_strings_h

#include "utils_basics.h"

int	compare_str(char *str1, char *str2);
int	check_word(const char *word, int word_len, const char *str);
int	compare_str_till_char(const char *env_name, const char *argument, char c);
int find_char_in_str(char c, const char *str);

#endif /* utils_strings_h */
