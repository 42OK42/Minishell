/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_middle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:28:21 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 16:28:11 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_signals(t_token *arg, t_data *data)
{
	counting_redirs(arg, data);
	signal(SIGINT, handle_sigint_l);
	signal(SIGQUIT, ft_handle_cat_backslash);
}

void	exec_child_m(t_token *args, t_data *data)
{
	close(data->fd2[0]);
	if (data->in_dirs == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
	}
	if (data->out_dirs == 0)
	{
		dup2(data->fd2[1], STDOUT_FILENO);
		close(data->fd2[1]);
	}
	exec_args4(args, data);
}

void	handle_middle(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = get_correct_args(args, data);
	prep_signals(arg, data);
	handle_in_redirection_m(arg, data);
	if (data->fd_in == -1 || data->infile_flag == 1)
	{
		close(data->fd2[1]);
		data->fd[0] = data->fd2[0];
		return ;
	}
	handle_out_redirection_m(arg, data);
	data->pids[data->x] = fork1();
	if (data->pids[data->x] == -1)
		exit(1);
	else if (data->pids[data->x] != 0)
		signal(SIGINT, SIG_IGN);
	else
		exec_child_m(arg, data);
	if (data->closed != -1)
		close(data->fd[0]);
	if (data->out_dirs == 0)
		close(data->fd2[1]);
	restore_std_io(data);
}

void	handle_in_redirection_m(t_token *args, t_data *data)
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

void	handle_out_redirection_m(t_token *args, t_data *data)
{
	if (data->out_dirs > 0)
	{
		close(data->fd2[1]);
		get_fd_out(args, data);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
}
