/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redir_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:25:23 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 03:16:03 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fd_out(t_token *args, t_data *data)
{
	char	*filename;
	int		i;

	i = 0;
	create_files(args, data);
	filename = get_outfile_name(args, data);
	i = get_file_type(args, data);
	if (i == 1)
		data->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (i == 2)
		data->fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->fd_out == -1 || i == 0)
		return ;
}

int	get_file_type(t_token *args, t_data *data)
{
	t_token	*arg;
	int		i;

	i = 0;
	arg = args;
	while (arg && i < data->out_dirs)
	{
		if (arg->type == OUT_REDIR || arg->type == APPEND)
			i++;
		if (i == data->out_dirs && arg->next)
		{
			if (arg->type == OUT_REDIR)
				return (1);
			if (arg->type == APPEND)
				return (2);
		}
		arg = arg->next;
	}
	return (0);
}

void	create_files(t_token *args, t_data *data)
{
	t_token	*arg;
	int		i;

	i = 0;
	arg = args;
	while (arg && i < data->out_dirs)
	{
		if (arg->type == OUT_REDIR || arg->type == APPEND)
		{
			if (arg->next)
				add_infile(data, arg->next->content);
			if (arg->type == OUT_REDIR && arg->next)
				data->fd_out = open(arg->next->content, data->open_flags, 0644);
			if (arg->type == APPEND && arg->next)
				data->fd_out = open(arg->next->content, data->app_flags, 0644);
			i++;
		}
		if (arg->next)
			arg = arg->next;
		else
			return ;
	}
}

char	*get_outfile_name(t_token *args, t_data *data)
{
	char	*filename;

	filename = get_correct_outfile(args, data);
	if (filename == NULL)
	{
		ft_perror("couldnt get outfilename\n");
		data->exit = 1;
		return (NULL);
	}
	return (filename);
}

char	*get_correct_outfile(t_token *args, t_data *data)
{
	t_token	*arg;
	int		i;

	i = 0;
	arg = args;
	while (arg && i < data->out_dirs)
	{
		if (arg->type == OUT_REDIR || arg->type == APPEND)
			i++;
		if (i == data->out_dirs && arg->next)
			return (arg->next->content);
		arg = arg->next;
	}
	return (NULL);
}
