/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:14:27 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 15:41:19 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_args2(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = get_correct_place(args);
	if (arg == NULL)
		return ;
	else if (arg->type == COMMAND)
		solo_command(data, arg);
	else if (arg->type == BUILT_IN)
		exec_built_ins(args, data);
	else if (arg->type == ARGUMENT)
		solo_argument(data, arg);
}

void	exec_args3(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = get_correct_place(args);
	if (arg == NULL)
		free_child(data, args);
	if (arg->type == COMMAND)
		exec_command(arg, data);
	if (arg->type == BUILT_IN)
		exec_built_ins(arg, data);
	if (arg->type == ARGUMENT)
	{
		if (arg->next && arg->next->type == ARGUMENT)
			arg = arg->next;
		exec_argument(arg, data);
	}
	free_child(data, args);
}

void	exec_args4(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = get_correct_place(args);
	if (arg == NULL)
		free_child(data, args);
	if (arg->type == COMMAND)
		exec_command(arg, data);
	if (arg->type == BUILT_IN)
		exec_built_ins(arg, data);
	if (arg->type == ARGUMENT)
	{
		if (arg->next && arg->next->type == ARGUMENT)
			arg = arg->next;
		exec_argument(arg, data);
	}
	free_child(data, args);
}

t_token	*get_correct_args(t_token *args, t_data *data)
{
	t_token	*arg;
	int		i;

	arg = args;
	i = 1;
	while (i < data->part)
	{
		while (arg->type != PIPE)
			arg = arg->next;
		i++;
		if (i < data->part)
			arg = arg->next;
	}
	if (data->part != 1)
		arg = arg->next;
	return (arg);
}

t_token	*get_correct_place(t_token *args)
{
	t_token	*arg;
	int		skip;

	arg = args;
	skip = 0;
	while (arg)
	{
		if (arg->type == IN_REDIR || arg->type == OUT_REDIR 
			|| arg->type == APPEND || arg->type == HERE_DOC)
		{
			skip = 1;
			arg = arg->next;
			continue ;
		}
		if (skip == 1)
		{
			arg = arg->next;
			skip = 0;
			continue ;
		}
		if (arg && (arg->type == ARGUMENT || arg->type == COMMAND 
				|| arg->type == BUILT_IN))
			return (arg);
	}
	return (NULL);
}
