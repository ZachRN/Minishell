//
//  fd_only_child.c
//  merged_mini_xcode_project
//
//  Created by Julia Demura on 12/09/2022.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "fd_only_child.h"
#include "fd_system_headers.h"
#include "fd_handl_utils.h"

#include "utils.h"

void	close_for_only_child(t_fd *fd)
{
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
	close_if_infile_if_heredoc_if_outfile(fd);
}

void fd_only_child(t_param *param)
{
	
	write_str_fd("\nONLY CHILD   ", STDOUT_FILENO);
	write_str_fd(param->cmd.command, STDOUT_FILENO);
	write_str_fd("\n", STDOUT_FILENO);
	if (param->in_flag == HEREDOC || param->in_flag == INFILE)
		param->fd.infile = get_fd_infile_or_heredoc(param->fd.heredoc, param->path_infile, param->in_flag);
	if (param->path_outfile != NULL)
		param->fd.outfile = open_outfile_with_without_append(param->in_flag, param->path_infile);
	close_for_only_child(&param->fd);
}
