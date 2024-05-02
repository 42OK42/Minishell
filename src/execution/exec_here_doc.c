/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:45:56 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/25 15:30:41 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	limit_error(t_data *data, char *end)
{
	ft_perror_arg_middle("warning: here-document delimited "
		"by end-of-file (wanted `", end, "')\n");
	data->exit = 0;
}

char	*execute_here_doc(t_data *data, char *end)
{
	char	*line;
	char	*result1;
	char	*result2;
	char	*result3;

	result1 = "";
	result3 = NULL;
	while (1 && g_sig_flag != 130)
	{
		line = readline("> ");
		if (line == NULL)
		{
			limit_error(data, end);
			return (result1);
		}
		if (ft_strcmp(line, end))
		{
			result2 = ft_strjoin(result1, line);
			result3 = ft_strjoin(result2, "\n");
			free(result2);
		}
		if (!ft_strcmp(line, end))
			return (result3);
	}
	return (result3);
}
