/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_beginning.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:28:01 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/03 14:25:31 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_b(t_token *args, t_data *data)
{
	close(data->fd[0]);
	if (data->out_dirs == 0)
	{
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		exec_args3(args, data);
	}
	else
	{
		close(data->fd[1]);
		exec_args3(args, data);
	}
}

void	handle_beginning(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = args;
	counting_redirs(arg, data);
	signal(SIGINT, handle_heredoc);
	if (data->here_doc > 0)
	{
		exec_here_doc(data, arg);
		//ft_printf("gsigflag%i\n", g_sig_flag);
		if (g_sig_flag == 130)
			data->exit = g_sig_flag;
	}
	signal(SIGINT, handle_sigint_l);
	if (pipe(data->fd) == -1)
	{
		ft_perror("couldnt create pipe");
		exit(1);
	}
	handle_in_redirection_b(arg, data);
	if (data->fd_in == -1 || data->infile_flag == 1)
	{
		close(data->fd[1]);
		return ;
	}
	handle_out_redirection_b(arg, data);
	data->pids[data->x] = fork1();
	if (data->pids[data->x] == -1)
		exit(1);
	else if (data->pids[data->x] == 0)
		exec_child_b(arg, data);
	close(data->fd[1]);
	restore_std_io(data);
}

void	handle_in_redirection_b(t_token *args, t_data *data)
{
	if (data->in_dirs > 0)
	{
		get_fd_in(args, data);
		if (data->fd_in == -1)
			return ;
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
}

void	handle_out_redirection_b(t_token *args, t_data *data)
{
	if (data->out_dirs > 0)
	{
		get_fd_out(args, data);
		if (data->fd_out == -1)
			return ;
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
}
