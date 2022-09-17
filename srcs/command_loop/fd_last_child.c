//
//  fd_last_child.c
//  merged_mini_xcode_project
//
//  Created by Julia Demura on 12/09/2022.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "fd_last_child.h"
#include "fd_system_headers.h"
#include "fd_handl_utils.h"

// no new pipe is created

void	close_for_last_child(t_fd *fd)
{
	close_if_infile_if_heredoc_if_outfile(fd);
//	if (close(fd->pipe[0]) < 0)
//		exit(1);
//	if (close(fd->pipe[1]) < 0)
//		exit(1);
}

void	fd_last_child(t_param *param)
{
	if (param->in_flag == INFILE || param->in_flag == HEREDOC) //what if I have INFILE and pipe? priority - file?
	{
		param->fd.infile = get_fd_infile_or_heredoc(param->fd.heredoc, param->path_infile, param->in_flag);
	}
	else
	{
		if (dup2(param->fd.temp_file, STDIN_FILENO) < 0) //pipe into temp so I can manage temp-pipe in parent process
			exit(1);
		close(param->fd.temp_file);
	}
	if (param->path_outfile != NULL)
	{
		param->fd.outfile = open_outfile_with_without_append(param->in_flag, param->path_infile);
	}
	close_for_last_child(&param->fd);
}
