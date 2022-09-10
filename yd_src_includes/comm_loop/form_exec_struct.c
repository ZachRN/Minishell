//
//  form_exec_struct.c
//  mini_codam
//
//  Created by Yuliia Demura on 9/6/22.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "form_exec_struct.h"
#include <stdlib.h>

t_cmd initiate_cmd_struct(char **args, char *comm_name, char **envp)
{
	t_cmd cmd;
	char **possible_path;

	cmd.cmd_args = args; //ready to use
	cmd.command = comm_name; //just a name that needs to be converted into path
	possible_path = find_possible_path_options_from_envp(envp);
	cmd.cmd_path = find_path(comm_name, possible_path); //NEED to work with path here
	return (cmd);
}

int	linked_list_size(t_parse *head)
{
	int res;
	t_parse *false_head;

	res = 0;
	false_head = head;
	if (head == NULL)
		return (-1); //no list wtf
	while (false_head != NULL)
	{
		res++;
		false_head = false_head->next;
	}
	return (res);
}

t_fd	initiate_fd_struct(int heredoc)
{
	t_fd fd;

	fd.infile = -1;
	fd.outfile = -1;
	fd.temp_file = -1;
	fd.pipe[0] = -1;
	fd.pipe[1] = -1;
	fd.heredoc = heredoc;
	fd.rdr_infile = -1;
	fd.rdr_outfile = -1;
	return (fd);
}

int initiate_each_param(t_param *par, t_parse *current, int i, char **envp)
{
	if (current == NULL)
		return (0);
	par->cmd = initiate_cmd_struct(current->args, current->cmd, envp); //path need to initiate
	par->fd	= initiate_fd_struct(current->hd_pipe);
	par->child_pid = -1;
	par->path_infile = current->infile;
	par->path_outfile = current->outfile;
	par->param_index = i;
	par->append = current->append;
	par->inlile_heredoc_flag = current->rd_in;
	if (current->next == NULL)
		return (0);
	return (1);
}

t_param	*fill_exec_struct(t_parse *head, int size, char **envp)
{
	int i;
	t_param *params;
	t_parse *temp_head;

	temp_head = head;
	params = malloc(sizeof(t_param) * size);
	if (params == NULL)
		exit(1);
	i = 0;
	while (i < size && temp_head != NULL)
	{
		if (initiate_each_param(params, temp_head, i, envp) == 0)
			break ;
		temp_head = temp_head->next;
		i++;
	}
	return (params);
}

t_exec form_input_for_execution(char **envp, t_together *input)
{
	t_exec exec;
	int size_exec;

	size_exec = linked_list_size(input->head);
	exec.params = fill_exec_struct(input->head, size_exec, envp);
	exec.comm_number = size_exec;
	exec.envp = envp;
	exec.index = 0;
	return (exec);
}
