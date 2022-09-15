//
//  form_exec_struct.c
//  mini_codam
//
//  Created by Yuliia Demura on 9/6/22.
//  Copyright © 2022 Yuliia Demura. All rights reserved.
//

#include "form_exec_struct.h"
#include "utils.h"
#include <stdlib.h>

#include <stdio.h>

int	if_built_in(const char *command)
{
	char *array_built_in[8];
	int i;

	i = 0;
	array_built_in[0] = "echo";
	array_built_in[1] = "cd";
	array_built_in[2] = "pwd";
	array_built_in[3] = "export";
	array_built_in[4] = "env";
	array_built_in[5] = "unset";
	array_built_in[6] = "exit";
	array_built_in[7] = NULL;
	while (i < 7)
	{
		if (compare_str(array_built_in[i], command) == TRU)
			return (TRU);;
		i++;
	}
	return (FLS);
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

t_cmd	initiate_cmd_struct(char **args, char *comm_name, char **envp)
{
	t_cmd cmd;
	char **possible_path;

	cmd.cmd_args = args;
	cmd.command = comm_name;
	possible_path = find_possible_path_options_from_envp(envp);
	cmd.cmd_path = find_path(comm_name, possible_path);
	if (if_built_in(comm_name) == TRU)
		cmd.type = BUILTIN;
	else
		cmd.type = NORMAL;
	free_my_lines(possible_path);
	return (cmd);
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

t_param initiate_each_param(t_parse *current, int i, char **envp)
{
	t_param param;

	param.cmd = initiate_cmd_struct(current->args, current->cmd, envp);
	param.fd = initiate_fd_struct(current->hd_pipe);
	param.child_pid = -1;
	param.path_infile = current->infile;
	param.path_outfile = current->outfile;
	param.param_index = i;
	param.append = current->append;
	param.in_flag = current->rd_in;
	return (param);
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
//		if (initiate_each_param(params, temp_head, i, envp) == 0)
//			break ;
		params[i] = initiate_each_param(temp_head, i, envp);
		temp_head = temp_head->next;
		i++;
		
	}
	return (params);
}

t_exec	form_input_for_execution(char **envp, t_together *input)
{
	t_exec exec;
	int size_exec;

	size_exec = linked_list_size(input->head);
	exec.params = fill_exec_struct(input->head, size_exec, envp);
	exec.comm_number = size_exec;
	exec.envp = envp;
	exec.index = 0;
	exec.upd_envp = NULL;
	return (exec);
}
