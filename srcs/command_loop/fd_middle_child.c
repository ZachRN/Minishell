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

void fd_middle_child(t_param *param)
{
	//what if I have INFILE and pipe? priority - file?
	if (param->in_flag == INFILE || param->in_flag == HEREDOC)
	{
		param->fd.infile = get_fd_infile_or_heredoc(param->fd.heredoc, param->path_infile, param->in_flag);
	}
	else
	{
		//pipe into temp so I can manage temp-pipe in parent process
		if (dup2(param->fd.temp_file, STDIN_FILENO) < 0)
			exit(1);
	}
	if (param->path_outfile == NULL)
	{
		if (dup2(param->fd.pipe[1], STDOUT_FILENO) < 0)
			exit(1);
	}
	
}
