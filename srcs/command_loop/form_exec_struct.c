/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   form_exec_struct.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yuliia <yuliia@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 11:31:33 by yuliia        #+#    #+#                 */
/*   Updated: 2022/09/19 13:37:23 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "form_exec_struct.h"
#include "utils.h"
#include <stdlib.h>

#include <stdio.h>

int	if_built_in(const char *command)
{
	char	*array_built_in[8];
	int		i;

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
			return (TRU);
		i++;
	}
	return (FLS);
}

int	linked_list_size(t_parse *head)
{
	int		res;
	t_parse	*false_head;

	res = 0;
	false_head = head;
	if (head == NULL)
		return (-1);
	while (false_head != NULL)
	{
		res++;
		false_head = false_head->next;
	}
	return (res);
}

t_cmd	initiate_cmd_struct(char **args, char *comm_name)
{
	t_cmd	cmd;

	cmd.cmd_args = args;
	cmd.command = comm_name;
	cmd.cmd_path = NULL;
	if (if_built_in(comm_name) == TRU)
		cmd.type = BUILTIN;
	else
		cmd.type = NORMAL;
	return (cmd);
}

t_param	initiate_each_param(t_parse *current, int i)
{
	t_param	param;

	param.cmd = initiate_cmd_struct(current->args, current->cmd);
	param.child_pid = -1;
	param.path_infile = current->infile;
	param.path_outfile = current->outfile;
	param.param_index = i;
	param.heredoc = current->heredoc;
	param.append = current->append;
	param.in_flag = current->rd_in;
	param.last_error = 0;
	return (param);
}

t_param	*fill_exec_struct(t_parse *head, int size)
{
	int		i;
	t_param	*params;
	t_parse	*temp_head;

	temp_head = head;
	params = malloc(sizeof(t_param) * size);
	if (params == NULL)
		exit(1);
	i = 0;
	while (i < size && temp_head != NULL)
	{
		params[i] = initiate_each_param(temp_head, i);
		temp_head = temp_head->next;
		i++;
	}
	return (params);
}
