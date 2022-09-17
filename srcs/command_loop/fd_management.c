//
//  fd_management.c
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//

#include "fd_management.h"
#include "fd_handl_utils.h"
#include "fd_system_headers.h"
#include "fd_only_child.h"
#include "fd_first_child.h"
#include "fd_middle_child.h"
#include "fd_last_child.h"

#include <stdio.h>

void	cleaning_heredocs_if_open(int current_index, int comm_number, t_fd *fd)
{
	int next_command_index;

	if (current_index == comm_number - 1)  ///last command, I will close heredoc further during closure management in child
		return ;
	next_command_index = current_index + 1;
	while (next_command_index != comm_number - 1)
	{
		if (fd[next_command_index].heredoc >= 0) ///if heredoc in next commands is open, I want to make sure they are all closed in current child, next child will inherit it all again from the parent
			if (close(fd[next_command_index].heredoc) < 0)
				exit(1);
		next_command_index++;
	}
}

void	pick_a_child(int i, int comm_number, t_param *params)
{
	cleaning_heredocs_if_open(i, comm_number, &params[i].fd);
	
	if (comm_number > 1 && i > 0)
	{
		params[i].fd.temp_file = params[i - 1].fd.temp_file;
	}
	
	
	if (comm_number == 1)
		fd_only_child(&params[i]);
	else
	{
		if (i == 0)
			fd_first_child(&params[i]);
		else if (i == comm_number - 1)
			fd_last_child(&params[i]);
		else
			fd_middle_child(&params[i]);
	}
}

void	manage_parent_fd(int index, int comm_numb, t_fd *fd)
{
	if (index != 0)
		close(fd->temp_file);
	fd->temp_file = fd->pipe[0];
	if (index != comm_numb - 1)
	{
		if (close(fd->pipe[1]) < 0)
			exit(1);
		fd->pipe[1] = -1;
	}
	
	
	close_if_infile_if_heredoc_if_outfile(fd);
	printf("parent1");
	if (fd->pipe[1] >= 0)
	{
		if (close(fd->pipe[1]) < 0)
			exit(1);
		fd->pipe[1] = -1;
	}
}














///Ok, the file desciprtors for redirections
///Every single node, has their indirect and out direct or any form of redirection initalized to some basic basic
///Infile -> NULL
///Outfile -> NULL
///If they are NULL, you did not get either of those as redirects, which means they dont exist

//Outfile
///It Oufile exists, it has a name, and if it has a name you then need to check the int append, if it is 1, you will append and add to the file, if it is 0, you truncate it and start the file over

//Infile
///if the Infile has a name, this is now the tricky part
///you need to use access to check if the file exists, if the file does not exist, you do not run the command at all, ive tested this with multiple commands and it is consistent (though you still run the previous command and pipe into the new command)
///If heredoc is >=0 that means it exists within a pipe, if it is -1 it was never called, and if it is -2 then i dont know how it got to you, but it shouldnt of
///Important to know, once I find a infile that doesn't exist, I stop parsing that command and just send you this "broken" command, which you will need to print an error message for, because I figured this was easier  to do in the child, then at parse
