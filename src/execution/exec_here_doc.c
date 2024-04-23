/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:45:56 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/23 20:06:48 by okrahl           ###   ########.fr       */
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
	char	*result;

	result = "";
	while (1 && g_sig_flag != 130)
	{
		line = readline("> ");
		if (line == NULL)
		{
			limit_error(data, end);
			return (result);
		}
		if (ft_strcmp(line, end))
		{
			result = ft_strjoin(result, line);
			result = ft_strjoin(result, "\n");
		}
		if (!ft_strcmp(line, end))
			return (result);
	}
	return (result);
}
