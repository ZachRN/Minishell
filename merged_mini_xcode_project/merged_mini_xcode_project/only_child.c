//
//  only_child.c
//  merged_mini_xcode_project
//
//  Created by Julia Demura on 12/09/2022.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "only_child.h"
#include "fd_handl_utils.h"
#include "system_headers_for_fd_management.h"

//One child
//If (comm_num == 1)
//{
//	in management
//	if (infile == NULL && no_heredoc)
//		fd_in = STDIN /default
//	else
//	{
//		else if (infile != NULL)
//			fd_in = open infile
//		else if (heredoc > 0)
//			fd_in = heredoc
//		dup2(fd_in, STDIN)
//	}
//
//}

//handle command FD when there is only one command

void	manage_fd_for_only_child(t_param *param, int index, int comm_number)
{
	if (param->in_flag == STDIN)
	{
		param->fd.infile = STDIN_FILENO; //default, no dups is needed?
	}
	else
	{
		if (param->in_flag == INFILE)
		{
			
		}
		else if (param->in_flag == HEREDOC)
		{
			
		}
		
		
	}
}
