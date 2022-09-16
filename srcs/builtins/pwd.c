//
//  pwd.c
//  minishell_xcd
//
//  Created by Julia Demura on 09/08/2022.
//

#include "pwd.h"
#include "builtin_utils.h"
#include <stdio.h>
#include <unistd.h>

//Type of errors in getcwd():
//
//1.EINVAL:The size argument is 0.
//2.ERANGE:The size argument is greater than 0, but is smaller than the length of the pathname +1.
//3.EACCES:Read or search permission was denied for a component of the pathname.
//4.ENOMEM:Insufficient storage space is available.
// SRC https://iq.opengenus.org/chdir-fchdir-getcwd-in-c/

/// in the shell the pwd command says something like “name too long” for paths over 1024 characters for mac

int	pwd_builtin(int fd)
{
	char buff[1024];
	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		perror("pwd");
		return (1);
	}
		
	else
	{
		write_str_fd(buff, fd);
		write_one_char_fd(fd, '\n');
	}
		
	return (0);
}

