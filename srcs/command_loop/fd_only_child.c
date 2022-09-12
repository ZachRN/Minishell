//
//  fd_only_child.c
//  merged_mini_xcode_project
//
//  Created by Julia Demura on 12/09/2022.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "fd_only_child.h"
#include "fd_system_headers.h"

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

void	close_for_only_child(t_fd *fd)
{
	if (close(fd->pipe[0]) < 0)
		exit(1);
	if (close(fd->pipe[1]) < 0)
		exit(1);
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
}

int	get_fd_infile_or_heredoc(int heredoc, const char *path_infile, int in_flag)
{
	int fd;

	fd = -1;
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

void fd_only_child(t_param *param)
{
	if (param->in_flag == STDIN)  /// if I even need this maybe it remains default and I am good
		param->fd.infile = STDIN_FILENO;
	else if (param->in_flag == HEREDOC || param->in_flag == INFILE)
	{
		param->fd.infile = get_fd_infile_or_heredoc(param->fd.heredoc, param->path_infile, param->in_flag);
	}
	if (param->path_outfile == NULL) /// if I even need this maybe it remains default and I am good
		param->fd.outfile = STDOUT_FILENO;
	else
		param->fd.outfile = open_outfile_with_without_append(param->in_flag, param->path_infile);
	close_for_only_child(&param->fd);
}
