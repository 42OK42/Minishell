/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:18:50 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 16:26:28 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_next_part(t_data *data)
{
	data->pipes = data->pipes - 1;
	data->part = data->part + 1;
	data->x = data->x + 1;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_args(t_token *args, t_data *data)
{
	t_token	*args_start;

	args_start = args;
	init_struct(data);
	counting(args, data);
	data->pids = malloc1(sizeof(pid_t) * (data->parts));
	while (args)
	{
		while (args && args->type != PIPE)
			args = args->next;
		handle_part(args_start, data);
		unlink_here_doc("Temp_hd");
		prep_next_part(data);
		if (args && args->next)
			args = args->next;
	}
	if (data->parts > 1)
		wait_for_children(data);
	prep_next_input(args_start, data);
}

void	wait_for_children(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < data->x)
	{
		waitpid(data->pids[i], &status, 0);
		data->exit = WEXITSTATUS(status);
		i++;
	}
}
