/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:30:10 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/13 00:25:52 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_only_spaces1(char *line)
{
	if (*line != ' ' && *line != '\t' && *line != '\v')
		return (0);
	return (1);
}

void	parsing(t_data *data)
{
	char	*line;
	int		flag;

	flag = 1;
	data->cat_flag = 0;
	data->quote_flag = NULL;
	while (flag)
	{
		line = readline("Enter a line: ");
		if (line == NULL)
		{
			free(line);
			free_data(data);
			flag = 0;
			break ;
		}
		if (line_only_spaces1(line) == 1)
			continue ;
		process_line(line, data);
		g_sig_flag = 0;
	}
}
