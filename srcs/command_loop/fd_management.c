//
//  fd_management.c
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//

#include "fd_management.h"
#include "fd_handl_utils.h"
#include "system_headers_for_fd_management.h"

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



void	redirect_open_dup_outfile(t_param *param)
{
	if (param->path_outfile != NULL)///redirection
	{
		if (param->append == 1)
		{
			param->fd.rdr_outfile = open(param->path_outfile, O_WRONLY | O_APPEND);
			if (param->fd.rdr_outfile < 0)
				exit(1);
			//what if file does not exist? or wrong permissions
		}
		else
		{
			param->fd.rdr_outfile = open(param->path_outfile, O_WRONLY | O_TRUNC);
			if (param->fd.rdr_outfile < 0)
				exit(1);
		}
		if (dup2(param->fd.rdr_outfile, STDOUT_FILENO) == -1)
			exit(1);
		param->fd.outfile = param->fd.rdr_outfile;
	}
	///do I need to close FD oufile previous and swap with this one?
}

void	redirect_open_infile(t_param *param)
{
	if (param->inlile_heredoc_flag != Infile)
	{
		if (param->inlile_heredoc_flag == Infile) ///R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.
		{
			if (access(param->path_infile, F_OK) < 0)
			{
				
			}
			//do not play this command
		}
		else if (param->fd.heredoc > 0)
		{
			if (dup2(param->fd.heredoc, STDIN_FILENO) == -1)
				exit(1);
		}
		///If heredoc is >=0 that means it exists within a pipe, if it is -1 it was never called, and if it is -2 then i dont know how it got to you, but it shouldnt of
		//maybe need to close heredoc
		
		//??
		///"broken" command, which you will need to print an error message for, because I figured this was easier  to do in the child, then at parse
	}
}

void	no_redirections_open(t_param *param, int index, int comm_number)
{
	if (index == 0) ///first_child
		direct_open_dup_infile(param->path_infile, &param->fd);
	else ///other children
	{
		if (dup2(param->fd.temp_file, STDIN_FILENO) == -1)
			exit(1);
	}
	if (index == comm_number - 1) ///last_child
		direct_open_dup_outfile(param->path_outfile, &param->fd);
	else ///other children
	{
		if (dup2(param->fd.pipe[1], STDOUT_FILENO) == -1)
			exit(1);
	}
}


void	opening_managemant(t_param *param, int index, int comm_number)
{
	if (param->path_infile == NULL && param->path_outfile == NULL && param->fd.heredoc < 0)
		no_redirections_open(param, index, comm_number);
	else
	{
		//dup pipes not for the 1st kid to make sure stdin out works correctly with redir
		//check if pipe needs to be closed here
		if (param->path_outfile != NULL)
		{
			redirect_open_dup_outfile(param);
		}
	}
	
}

void	close_management(t_fd *fd, int index, int comm_number)
{
	if (index == 0 && fd->infile >= 0)///first
	{
		if (close(fd->infile) < 0)
			exit(1);
	}
	else if (index != comm_number && index > 0)///rest
	{
		if (close(fd->pipe[0]) < 0)
			exit(1);
		if (close(fd->pipe[1]) < 0)
			exit(1);
	}
	else if (index == comm_number && fd->outfile >= 0)///last
	{
		if (close(fd->outfile) < 0)
			exit(1);
	}
}

void	pick_fd_for_child(t_param *param, int index, int comm_number)
{
	opening_managemant(param, index, comm_number);
	close_management(&param->fd, index, comm_number);
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
	}
}
