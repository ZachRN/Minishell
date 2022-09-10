//
//  fd_handl_utils.c
//  x_mini
//
//  Created by Julia Demura on 10/09/2022.
//

#include "fd_handl_utils.h"
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

void	direct_open_dup_infile(const char *infile, t_fd *fd)
{
	if (infile != NULL)
	{
		fd->infile = open(infile, O_RDONLY);
		if (fd->infile < 0)
			exit(1);
		if (dup2(fd->infile, STDIN_FILENO) == -1)
			exit(1);
	}
}

void	direct_open_dup_outfile(const char *outfile, t_fd *fd)
{
	if (outfile != NULL)
	{
		fd->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd->outfile < 0)
			exit(1);
		if (dup2(fd->outfile, STDOUT_FILENO) == -1)
			exit(1);
	}
}
