//
//  pwd.c
//  minishell_xcd
//
//  Created by Julia Demura on 09/08/2022.
//

#include "pwd.h"

//getcwd():
//The getcwd() function places an absolute pathname of the current working directory in the array pointed to by buf, and returns buf. The size argument is the size in bytes of the character array pointed to by the buf argument. If buf is a null pointer, the behaviour of getcwd() is undefined.The return value represent our current working directory.
//
//Function declaration:
//
//char *getcwd(char *buf, size_t size);
//CCopy
//Function return :The getcwd() function returns a pointer which points to a character array where the path of current working directory is stored.In case the path is not found then it returns a null pointer and the contents of the array are undefined and the errno is set to indicate the type of error.
//
//Type of errors in getcwd():
//
//1.EINVAL:The size argument is 0.
//2.ERANGE:The size argument is greater than 0, but is smaller than the length of the pathname +1.
//3.EACCES:Read or search permission was denied for a component of the pathname.
//4.ENOMEM:Insufficient storage space is available.
// SRC https://iq.opengenus.org/chdir-fchdir-getcwd-in-c/


int	pwd_builtin(void)
{
	char buff[1024]; /// in the shell the pwd command says something like “name too long” for paths over 1024 characters for mac

	if (getcwd(buff, sizeof(buff)) == NULL)
		return (ERR); //use perror here?
	else
		printf("%s\n", buff); /// dont know if \n is needed
	///yuliia@Julias-MacBook-Air ~ % pwd
	///	/Users/yuliia
	/// yuliia@Julias-MacBook-Air ~ %
	/// looks like there is newline automatically and not just new line but terminal line, need to test
	
	
	return (0);
}

