//
//  echo.c
//  minishell_xcd
//
//  Created by Julia Demura on 02/08/2022.
//

#include "echo.h"
#include "builtin_utils.h"
#include <stdlib.h>

//echo $ENV_VAR - gives the value of this var
// - echo env
/// • Handle environment variables ($ followed by a sequence of characters) which should expand to their values

///	echo $COLORTERMOKBKK - newline if no env
//
//
//int	handle_env_var(char *name, char newline)
//{
//	char *found_value;
//
//	if (*name == '$')
//		name++;
//	found_value = getenv(name);
//	if (found_value == NULL)
//		write(1, &newline, 1);
//	else
//		printf("%s\n", found_value);
//	return (0);
//}

int	echo_builtin(int synopsis, char **str)
{
	int i;

	i = 0;
//	if (*str[0] == '$')
//		handle_env_var(*str++, '\n');
	while (str[i] != NULL && compare_str("-n", str[i]) == 1)
		i++;
	while (str[i] != NULL)
	{
		write_str_fd(str[i], 1);
		if (str[i + 1] != NULL)
			write_one_char_fd(1, ' ');
		i++;
	}
	if (synopsis > 0) ///if synopsis == -1 there is non
		write_one_char_fd(1, '\n');
	return (0);
}
