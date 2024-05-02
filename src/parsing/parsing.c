/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:30:10 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/25 16:24:57 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_only_spaces1(char *line)
{
	if (*line != ' ' && *line != '\t' && *line != '\v')
		return (0);
	return (1);
}

void	handle_flag(t_data *data)
{
	data->exit = g_sig_flag;
	g_sig_flag = 0;
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
		if (g_sig_flag != 0)
			handle_flag(data);
		signal(SIGINT, handle_sigint_include_rd);
		line = readline("minishell: ");
		if (g_sig_flag != 0)
			handle_flag(data);
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
	}
}
