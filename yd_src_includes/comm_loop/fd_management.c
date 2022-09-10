//
//  fd_management.c
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//


///*
//	manage_fd.c
//	pipex
//
//	Created by Yuliia Demura on 11/16/21.
//	Copyright © 2021 Yuliia Demura. All rights reserved.
//*/
//
//#include "manage_fd.h"
//
//void	close_childs_pipe_end(int i, t_params *params, t_fd *fd)
//{
//	if (i == 0)
//	{
//		if (close(fd->infile) < 0)
//			exit_beautifully("close failed, manage_fd.c:31", ERR);
//	}
//	if (i != params->index - 1)
//	{
//		if (close(fd->pipe[0]) < 0)
//			exit_beautifully("close failed, manage_fd.c:29", ERR);
//		if (close(fd->pipe[1]) < 0)
//			exit_beautifully("close failed, manage_fd.c:30", ERR);
//	}
//	if (i == params->index - 1)
//	{
//		if (close(fd->outfile) < 0)
//			exit_beautifully("close failed, manage_fd.c:31", ERR);
//	}
//}
//
//void	first_child(t_params *params, t_fd *fd)
//{
//	fd->infile = open(params->path_infile, O_RDONLY);
//	if (fd->infile < 0)
//		exit_beautifully("open failed us in manage_fd.c:39", ERR);
//	if (dup2(fd->infile, STDIN_FILENO) == -1)
//		exit_beautifully("dup2 failed, manage_fd.c: 41", ERR);
//}
//
//
//
//
//
//void	pick_fd_for_child(int i, t_params *params, t_fd *fd)
//{
//	if (i == 0)
//		first_child(params, fd);
//	else
//	{
//		if (dup2(fd->temp_file, STDIN_FILENO) == -1)
//			exit_beautifully("dup2 failed, manage_fd.c:46", ERR);
//	}
//	if (i == params->index - 1)
//	{
//		fd->outfile = open(params->path_outfile, O_WRONLY | O_CREAT | O_TRUNC,
//				0644);
//		if (fd->outfile < 0)
//			exit_beautifully("open failed us in manage_fd.c:52", ERR);
//		if (dup2(fd->outfile, STDOUT_FILENO) == -1)
//			exit_beautifully("dup2 failed, manage_fd.c:54", ERR);
//	}
//	else
//	{
//		if (dup2(fd->pipe[1], STDOUT_FILENO) == -1)
//			exit_beautifully("dup2 failed, manage_fd.c:59", ERR);
//	}
//	close_childs_pipe_end(i, params, fd);
//}
//
//
//
//
//
//void	manage_parent_fd(int i, t_params *params, t_fd *fd)
//{
//	if (i != 0)
//		close(fd->temp_file);
//	fd->temp_file = fd->pipe[0];
//	if (i != params->index - 1)
//	{
//		if (close(fd->pipe[1]) < 0)
//			exit_beautifully("close failed, manage_fd.c:72", ERR);
//	}
//}


//EXAMPLE ABOVE FR PIPEX


#include "fd_management.h"

void	open_dup_infile(const char *path, t_fd *fd)
{
	fd->infile = open(path, O_RDONLY);
	if (fd->infile < 0)
		exit(1);
	if (dup2(fd->infile, STDIN_FILENO) == -1)
		exit(1);
}

void	open_dup_outfile(const char *path, t_fd *fd)
{
	fd->outfile = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd->outfile < 0)
		exit(1);
	if (dup2(fd->outfile, STDOUT_FILENO) == -1)
		exit(1);
}

void	opening_managemant(t_param *param, int index, int comm_number)
{
	if (index == 0) ///		first_child
		open_dup_infile(param->path_infile, &param->fd);
	else ///	other children
	{
		if (dup2(param->fd.temp_file, STDIN_FILENO) == -1)
			exit(1);
	}
	if (index == comm_number - 1) ///	last_child
		open_dup_outfile(param->path_outfile, &param->fd);
	else ///	other children
	{
		if (dup2(param->fd.pipe[1], STDOUT_FILENO) == -1)
			exit(1);
	}
}


























void	close_management(t_fd *fd, int index, int comm_number)
{
	if (index == 0)
	{
		if (close(fd->infile) < 0)
			exit(1);
	}
}


void	pick_fd_for_child(t_param *param, int index, int comm_number)
{
	opening_managemant(param, index, comm_number);
	close_management(&param->fd, index, comm_number);
			
}






//	if first child

// if last child

//middle

