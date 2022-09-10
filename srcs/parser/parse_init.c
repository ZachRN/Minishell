/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 17:55:24 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/10 15:27:51 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"

/*
The Parser is a one way linked list
Cmd is the command name
Args is the list of all the arguements and cmd name at the front for execve
outfile is the name where to put the output redirection
Append is a code on how to open the file, 1 being to append, 0 to overwrite the
file
Infile the file to take information from for the commands
Heredoc_pipe is a file descriptor that when >= 0 is open and has information
stored within a pipe for us to use. -1 being it wasnt set and -2 an error
occured within the heredoc handling
Next is just the next link in the chain.
*/

t_parse	*parse_initalize(void)
{
	t_parse	*head;

	head = (t_parse *)malloc(sizeof(t_parse));
	if (!head)
		return (NULL);
	head->cmd = NULL;
	head->args = NULL;
	head->outfile = NULL;
	head->append = -1;
	head->infile = NULL;
	head->hd_pipe = -1;
	head->next = NULL;
	return (head);
}
