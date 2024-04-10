/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:18:50 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/03 14:24:05 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_next_line(t_data *data)
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
		unlink_here_doc(".Here_doc");
		prep_next_line(data);
		if (args && args->next)
			args = args->next;
	}
	if (data->parts > 1 && g_sig_flag != 130) // fickt das was? Zum beispiel cat????? das muss geskipped werden wenn heredoc executed wurde
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
