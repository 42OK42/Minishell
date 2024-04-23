/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:25:55 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/23 20:03:16 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*exec_here_doc2(t_token *args, t_data *data)
{
	char	*str;
	t_token *start;
	t_token	*temp;

	start = args;
	while (args)
	{
		if (args->type == HERE_DOC && args->next)
		{
			str = execute_here_doc(data, args->next->content);
			temp = args->next;
			args->next = args->next->next;
			//free_token(temp);
			free(args->content);
			args->content = str;
			args->type = HD_PREP;
		}
		args = args->next;
	}
	return (start);
}

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
	t_token	*first_token2;
	t_token	*last_token;

	first_token = NULL;
	first_token2 = NULL;
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
		signal(SIGINT, handle_heredoc);
		first_token2 = exec_here_doc2(first_token, data);
		if (g_sig_flag == 130)
			data->exit = g_sig_flag;
		signal(SIGINT, handle_sigint);
		print_args(first_token2);
		//exec_args(first_token2, data);
	}
}
