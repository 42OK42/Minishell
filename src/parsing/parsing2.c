/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:25:55 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/04 23:31:48 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_tokens(char **words, t_data *data, \
	t_token **first_token, t_token **last_token)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		*last_token = add_token(*last_token, words[i], data, i);
		if (*first_token == NULL)
			*first_token = *last_token;
		i++;
	}
}

int	process_input_line(char *line, t_data *data, \
t_token **first_token, t_token **last_token)
{
	char	**words;

	add_history(line);
	data->command_flag = 0;
	if (find_dollar(line) == 1)
		line = expand(line, data);
	if (line == NULL)
		return (1);
	line = add_spaces(line);
	words = ft_split_modified(line, ' ', data);
	if (quote_bullshit(words, data) == 0)
	{
		free_words(words);
		free(line);
		free_quote_flag(data);
		data->exit = 42;
		return (-1);
	}
	process_tokens(words, data, first_token, last_token);
	free_words(words);
	free(line);
	return (1);
}

void	process_line(char *line, t_data *data)
{
	t_token	*first_token;
	t_token	*last_token;

	first_token = NULL;
	last_token = NULL;
	if (line && *line)
	{
		add_history(line);
		if (process_input_line(line, data, &first_token, &last_token) == -1)
			return ;
		if (line == NULL)
		{
			data->exit = 130;
			free(line);
			return ;
		}
		if (handle_errors(first_token) == -1)
		{
			free_list(first_token);
			data->exit = 2;
			return ;
		}
		free_quote_flag(data);
		print_args(first_token);
		exec_args(first_token, data);
	}
}
