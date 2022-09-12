//
//  fd_only_child.c
//  merged_mini_xcode_project
//
//  Created by Julia Demura on 12/09/2022.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "fd_only_child.h"
#include "fd_system_headers.h"

int		open_infile_with_without_append(int append, const char *path)
{
	int fd;

	fd = -1;
	if (append == 1)
	{
		fd = open(path, O_WRONLY | O_APPEND);
		if (fd < 0)
			exit(1);
	}
	else
	{
		fd = open(path, O_WRONLY | O_TRUNC);
		if (fd < 0)
			exit(1);
	}
	return (fd);
}





void fd_only_child(t_param *param, int index, int comm_number)
{
	if (param->in_flag == STDIN)
	{
		param->fd.infile = STDIN_FILENO; /// if I even need this maybe it remains default and I am good
	}
	else
	{
		if (param->in_flag == INFILE)
		{
			param->fd.infile = open_infile_with_without_append(param->in_flag, param->path_infile);
		}
		else if (param->in_flag == HEREDOC)
		{
			
		}
	}
	
	
	
}
