/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:06:44 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 16:25:51 by bschmidt         ###   ########.fr       */
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
		if (arg->type == COMMAND && ft_strcmp(arg->content, "./minishell") == 0)
		{
			increase_sh_level(data);
			exec_command(arg, data);
		}
		else if (arg->type == COMMAND)
			exec_command(arg, data);
	}
	else
		signal(SIGINT, SIG_IGN);
	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		data->exit = WEXITSTATUS(status);
}
