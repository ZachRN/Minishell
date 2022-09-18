#include "built_in_set.h"
#include "path_search.h"
#include "signal_handles.h"
#include "struct.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void	parent_pipe(t_exec *exec, int i, t_fd_two *fd)
{
	if (i != 0)
	{
		fd->storage = fd->pipe[0];
		fd->pipe[0] = -1;
	}
	if (i < exec->comm_number)
	{
		if (pipe(fd->pipe) < 0)
			exit(1);
	}
}

int	check_infile_outfile(t_exec *exec)
{
	int fd;

	if (exec->params[exec->index].in_flag == Infile)
	{
		fd = open(exec->params[exec->index].path_infile, O_RDONLY);
		if (fd < 0)
			perror("minishell");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (exec->params[exec->index].in_flag == Heredoc)
	{
		fd = open(exec->params[exec->index].heredoc, O_RDONLY);
		if (fd < 0)
			perror("minishell");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (exec->params[exec->index].append == 0)
	{
		fd = open(exec->params[exec->index].path_outfile, (O_TRUNC | O_WRONLY));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (exec->params[exec->index].append == 1)
	{
		fd = open(exec->params[exec->index].path_outfile, (O_APPEND | O_WRONLY));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (STDOUT_FILENO);
}

int	handle_child_fd(t_exec *exec, int i, t_fd_two *fd)
{
	if (fd->storage != -1)
	{
		dup2(fd->storage, STDIN_FILENO);
		close(fd->storage);
	}
	if (fd->pipe[1] != -1 && i != exec->comm_number - 1)
	{
		dup2(fd->pipe[1], STDOUT_FILENO);
		close(fd->pipe[1]);
	}
	else if (fd->pipe[1] != -1)
		close(fd->pipe[1]);
	if (fd->pipe[0] != -1)
		close(fd->pipe[0]);
	return (check_infile_outfile(exec));
}

void	zach_stuff(t_exec *exec, int i, t_fd_two *fd)
{
	exec->params[i].child_pid = fork();
	if (exec->params[i].child_pid < 0)
		exit(1);
	if (exec->params[i].child_pid == 0)
	{
		if (check_assess_to_file(exec->params[i].path_infile) < 0)
			exit(1);
		signal_director(DEFAULT_SIG);
		handle_child_fd(exec, i, fd);
		exec->params[i].cmd.cmd_path = find_command_path(exec->params[i].cmd, exec->envp);
		if (exec->params[i].cmd.type == BUILTIN)
			enviromental_variable_function(exec, exec->params[i].cmd.cmd_args, STDOUT_FILENO);
		else
			execve(exec->params[i].cmd.cmd_path, exec->params[i].cmd.cmd_args, exec->envp);
		exit(1);
	}
	if (i != 0)
	{
		close(fd->storage);
		fd->storage = -1;
	}
	if (exec->comm_number == 1)
	{
		close(fd->pipe[0]);
		close(fd->pipe[1]);
	}
	close(fd->pipe[1]);
	fd->pipe[1] = -1;
}

char	**handle_one_param_set_two(t_exec *exec, int i, t_fd_two *fd)
{
	char	**new_envp;

	new_envp = NULL;
	//WHEN IT IS ONLY ONE IT DOES NOT WRITE TO THE CORRECT AREA
	//IF IT IS A BUILT IN
	if (exec->index == 0 && exec->params[i].cmd.type == BUILTIN && exec->comm_number == 1)
	{
		close(fd->pipe[0]);
		close(fd->pipe[1]);
		return (enviromental_variable_function(exec, exec->params[i].cmd.cmd_args, STDOUT_FILENO));
	}
	else
		zach_stuff(exec, i, fd);
	return (NULL);
}
