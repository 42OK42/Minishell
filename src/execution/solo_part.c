/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:06:44 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/23 18:27:30 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	solo_command(t_data *data, t_token *arg)
{
	int	status;

	status = 0;
	data->pid = fork1();
	if (data->pid == 0)
		exec_command(arg, data);
	waitpid(data->pid, &status, 0);
	data->exit = WEXITSTATUS(status);
}

void	solo_argument(t_data *data, t_token *arg)
{
	int	status;

	status = 0;
	data->pid = fork1();
	if (data->pid == 0)
	{
		if (arg->type == ARGUMENT)
			exec_argument(arg, data);
		if (arg->type == COMMAND)
			exec_command(arg, data);
	}
	else
		signal(SIGINT, SIG_IGN);
	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		data->exit = WEXITSTATUS(status);
}
