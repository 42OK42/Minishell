/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:23:00 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 15:19:17 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fd_in(t_token *args, t_data *data)
{
	char	*filename;
	t_token	*arg;

	arg = args;
	filename = get_infile_name(arg, data);
	if (filename)
		check_infile(data, filename);
	if (data->hd_flag == 0 && filename)
		data->fd_in = open(filename, O_RDONLY);
	if (data->hd_flag == 0 && filename == NULL)
		data->fd_in = -1;
	if (data->hd_flag == 1)
		data->fd_in = open(".Here_doc", O_RDONLY);
	if (data->fd_in == -1)
	{
		if (filename)
			ft_perror_arg(filename, " : No such file or directory\n");
		else
			ft_perror("Input: No such file or directory\n");
		return ;
	}
	return ;
}

char	*get_infile_name(t_token *args, t_data *data)
{
	char	*filename;

	filename = get_correct_infile(args, data);
	if (filename == NULL)
	{
		data->exit = 1;
		return (NULL);
	}
	return (filename);
}

char	*get_correct_infile(t_token *args, t_data *data)
{
	t_token	*arg;
	int		i;

	i = 0;
	arg = args;
	while (arg && i < data->in_dirs)
	{
		if (arg->type == IN_REDIR || arg->type == HERE_DOC)
			i++;
		if (i == data->in_dirs && arg->next)
		{
			if (arg->type == IN_REDIR)
				return (arg->next->content);
			if (arg->type == HERE_DOC)
			{
				data->hd_flag = 1;
				return (".Here_doc");
			}
		}
		arg = arg->next;
	}
	return (NULL);
}
