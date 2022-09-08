//
//  utils_basics.h
//  x_mini
//
//  Created by Julia Demura on 06/09/2022.
//

#ifndef utils_basics_h
#define utils_basics_h

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
