/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:23:00 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 16:42:42 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_here_doc(t_token *args, t_data *data)
{
	t_token	*arg;
	char	*temp;
	int		fd;

	temp = NULL;
	arg = args;
	while (arg && arg->type != PIPE)
	{
		if (arg->type == HD_PREP)
			temp = arg->content;
		arg = arg->next;
	}
	if (temp == NULL)
		return ;
	fd = open("Temp_hd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, temp, ft_strlen(temp));
	close(fd);
	data->fd_in = open("Temp_hd", O_RDONLY, 0644);
}

void	get_fd_in(t_token *args, t_data *data)
{
	t_token	*arg;

	arg = args;
	while (args && args->type != PIPE)
	{
		if (args->type == IN_REDIR)
			data->fd_in = open(args->next->content, O_RDONLY);
		if (data->fd_in == -1)
		{
			if (args->next->content)
				ft_perror_arg(args->next->content, \
					": No such file or directory\n");
			else
				ft_perror("Input: No such file or directory\n");
			data->exit = 1;
			return ;
		}
		args = args->next;
	}
	if (data->hd_flag == 1)
		read_here_doc(arg, data);
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
		if (arg->type == IN_REDIR || arg->type == HD_PREP)
			i++;
		if (i == data->in_dirs)
		{
			if (arg->type == IN_REDIR && arg->next)
				return (arg->next->content);
		}
		arg = arg->next;
	}
	return (NULL);
}
