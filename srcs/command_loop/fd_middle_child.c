//
//  fd_middle_child.c
//  merged_mini_xcode_project
//
//  Created by Julia Demura on 12/09/2022.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "fd_middle_child.h"
#include "fd_system_headers.h"
#include "fd_handl_utils.h"

#include "utils.h"

void	close_for_middle_child(t_fd *fd)
{
	close_if_infile_if_heredoc_if_outfile(fd);
	if (fd->pipe[0] >= 0)
	{
		if (close(fd->pipe[0]) < 0)
			exit(1);
		fd->pipe[0] = -1;
	}
	if (fd->pipe[1] >= 0)
	{
		if (close(fd->pipe[1]) < 0)
			exit(1);
		fd->pipe[1] = -1;
	}
	if (fd->temp_file >= 0)
	{
		if (close(fd->temp_file) < 0)
			exit(1);
		fd->temp_file = -1;
	}
}

void	middle_child_outfile_fd_management(t_param *param)
{
	if (param->path_outfile	== NULL)
	{
		if (dup2(param->fd.pipe[1], STDOUT_FILENO) < 0)
			exit(1);
	}
	else
	{
		param->fd.outfile = open_outfile_with_without_append(param->append, param->path_outfile);
		if (dup2(param->fd.outfile, STDOUT_FILENO) < 0)
			exit(1);
	}
}

void	fd_middle_child(t_param *param)
{
	write_str_fd("\nMIDDLE CHILD   ", STDOUT_FILENO);
	write_str_fd(param->cmd.command, STDOUT_FILENO);
	write_str_fd("\n", STDOUT_FILENO);
	if (param->in_flag == INFILE || param->in_flag == HEREDOC) //what if I have INFILE and pipe? priority - file?
	{
		param->fd.infile = get_fd_infile_or_heredoc(param->fd.heredoc, param->path_infile, param->in_flag);
	}
	else
	{
		if (dup2(param->fd.temp_file, STDIN_FILENO) < 0) //pipe into temp so I can manage temp-pipe in parent process
			exit(1);
	}
	if (param->path_outfile == NULL)
	{
		if (dup2(param->fd.pipe[1], STDOUT_FILENO) < 0)
			exit(1);
	}
	middle_child_outfile_fd_management(param);
	close_for_middle_child(&param->fd);
}
