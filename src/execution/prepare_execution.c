/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:20:19 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 15:07:02 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_data *data)
{
	data->pipes = 0;
	data->args = 0;
	data->cmds = 0;
	data->in_dirs = 0;
	data->out_dirs = 0;
	data->part = 1;
	data->fd_in = 0;
	data->fd_out = 0;
	data->fd2[0] = -1;
	data->fd2[1] = -1;
	data->x = 0;
	data->solo = 0;
	data->closed = 0;
	data->saved_stdout = dup(STDOUT_FILENO);
	data->saved_stdin = dup(STDIN_FILENO);
	data->files = malloc1(sizeof(char *) * 1);
	data->files[0] = NULL;
	data->open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	data->app_flags = O_WRONLY | O_CREAT | O_APPEND;
}

void	counting(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = args;
	while (arg)
	{
		if (arg->type == PIPE)
			data->pipes++;
		arg = arg->next;
	}
	data->parts = data->pipes + 1;
}
