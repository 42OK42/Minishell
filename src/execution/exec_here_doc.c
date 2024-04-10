/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:45:56 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/22 19:57:34 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	limit_error(t_data *data, char *end)
{
	ft_perror_arg_middle("warning: here-document delimited "
		"by end-of-file (wanted `", end, "')\n");
	data->exit = 0;
}

void	handle_here_doc(t_data *data, char *end, int fd_out)
{
	char	*line;

	while (1 && g_sig_flag != 130)
	{
		ft_printf("%d",g_sig_flag);
		line = readline("> ");
		if (line == NULL)
		{
			limit_error(data, end);
			break ;
		}
		if (!ft_strcmp(line, end))
		{
			free(line);
			break ;
		}
		write(fd_out, line, strlen(line));
		write(fd_out, "\n", 1);
		free(line);
	}
}

void	exec_here_doc(t_data *data, t_token *args)
{
	char	*end;
	int		fd_out;
	t_token	*tmp;

	tmp = args;
	data->i++;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != HERE_DOC)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->next)
			end = tmp->next->content;
		else
			return ;
		fd_out = open(".Here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			return (perror("Error opening file Here_doc"));
		handle_here_doc(data, end, fd_out);
		if (close(fd_out) == -1)
			perror("Error closing file Here_doc");
		tmp = tmp->next;
	}
}
