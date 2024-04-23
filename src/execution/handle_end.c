/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:28:35 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/23 19:31:18 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_e(t_token *args, t_data *data)
{
	printf("Die Prozess-ID ist: %d\n", getpid());
	if (data->in_dirs == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		exec_args4(args, data);
	}
	else
	{
		close(data->fd[0]);
		exec_args4(args, data);
	}
}

int	check_in_redir(t_data *data)
{
	if (data->fd_in == -1 || data->infile_flag == 1)
	{
		close(data->fd[0]);
		restore_std_io(data);
		return (1);
	}
	else
		return (0);
}

void	handle_end(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = get_correct_args(args, data);
	counting_redirs(arg, data);
	signal(SIGINT, handle_sigint_l);
	handle_in_redirection_e(arg, data);
	if (check_in_redir(data) == 1)
		return ;
	handle_out_redirection_e(arg, data);
	if (data->fd_out == -1)
	{
		restore_std_io(data);
		return ;
	}
	data->pids[data->x] = fork1();
	if (data->pids[data->x] == -1)
		exit(1);
	else if (data->pids[data->x] != 0)
		signal(SIGINT, SIG_IGN);
	else
		exec_child_e(arg, data);
	if (data->closed != -1)
		close(data->fd[0]);
	restore_std_io(data);
}

void	handle_in_redirection_e(t_token *args, t_data *data)
{
	if (data->in_dirs > 0)
	{
		close(data->fd[0]);
		data->closed = -1;
		get_fd_in(args, data);
		if (data->fd_in == -1)
			return ;
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
}

void	handle_out_redirection_e(t_token *args, t_data *data)
{
	if (data->out_dirs > 0)
	{
		get_fd_out(args, data);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
}
