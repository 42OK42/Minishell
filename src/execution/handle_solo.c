/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_solo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:28:53 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 15:52:26 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_solo(t_token *args, t_data *data)
{
	counting_redirs(args, data);
	signal(SIGINT, handle_sigint_l);
	signal(SIGQUIT, ft_handle_cat_backslash);
	handle_in_redirection_s(args, data);
	if (data->fd_in == -1)
	{
		restore_std_io(data);
		return ;
	}
	handle_out_redirection_s(args, data);
	if (data->infile_flag == 1)
	{
		restore_std_io(data);
		return ;
	}
	exec_args2(args, data);
	restore_std_io(data);
}

void	handle_in_redirection_s(t_token *args, t_data *data)
{
	if (data->in_dirs > 0)
	{
		get_fd_in(args, data);
		dup2(data->fd_in, STDIN_FILENO);
	}
}

void	handle_out_redirection_s(t_token *args, t_data *data)
{
	if (data->out_dirs > 0)
	{
		get_fd_out(args, data);
		dup2(data->fd_out, STDOUT_FILENO);
	}
}

void	restore_std_io(t_data *data)
{
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
}
