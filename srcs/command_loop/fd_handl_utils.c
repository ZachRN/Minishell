//
//  fd_handl_utils.c
//  x_mini
//
//  Created by Julia Demura on 10/09/2022.
//

#include "fd_handl_utils.h"
#include "fd_system_headers.h"

void	close_if_infile_if_heredoc_if_outfile(t_fd *fd)
{
	if (fd->heredoc >= 0)
	{
		if (close(fd->heredoc) < 0)
			exit(1);
	}
	if (fd->infile >= 0)
	{
		if (close(fd->infile) < 0)
			exit(1);
	}
	if (fd->outfile >= 0)
	{
		if (close(fd->infile) < 0)
			exit(1);
	}
}

int		open_outfile_with_without_append(int append, const char *path)
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


int	get_fd_infile_or_heredoc(int heredoc, const char *path_infile, int in_flag)
{
	int fd;

	fd = STDIN_FILENO;
	if (in_flag == INFILE)
	{
		fd = open(path_infile, O_RDONLY);
		if (fd < 0)
			exit(1);
	}
	else if (in_flag == HEREDOC)
		fd = heredoc;
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(1);
	return (fd);
}
