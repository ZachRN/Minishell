//
//  fd_first_child.c
//  merged_mini_xcode_project
//
//  Created by Julia Demura on 12/09/2022.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "fd_first_child.h"
#include "fd_system_headers.h"
#include "fd_handl_utils.h"

void	close_for_first_child(t_fd *fd)
{
	close_if_infile_if_heredoc_if_outfile(fd);
	if (close(fd->pipe[0]) < 0)
		exit(1);
	if (close(fd->pipe[1]) < 0)
		exit(1);
}

void	fd_first_child(t_param *param)
{
	if (param->in_flag == HEREDOC || param->in_flag == INFILE)
	{
		param->fd.infile = get_fd_infile_or_heredoc(param->fd.heredoc, param->path_infile, param->in_flag);
	}
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
	close_for_first_child(&param->fd);
}
