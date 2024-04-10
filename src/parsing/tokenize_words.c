/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:11:34 by okrahl            #+#    #+#             */
/*   Updated: 2024/02/29 17:24:24 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_token_type(char *word, t_data *data, int word_index, t_token *last)
{
	t_type	redir_type;
	char	*command_path;

	redir_type = check_redirections(word, data, word_index);
	if (last && is_redirection(last->type))
		return (ARGUMENT);
	if (redir_type != ARGUMENT)
		return (redir_type);
	if (is_builtin(word))
		return (BUILT_IN);
	command_path = find_command_path(word);
	if (command_path != NULL)
	{
		free(command_path);
		return (COMMAND);
	}
	if (ft_strcmp(word, "|") == 0)
		return (PIPE);
	return (ARGUMENT);
}

t_token	*create_token(char *word, t_data *data, int word_index, t_token *last)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->content = ft_strdup(word);
	token->type = get_token_type(word, data, word_index, last);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*add_token(t_token *last, char *word, t_data *data, int word_index)
{
	t_token	*token;

	token = create_token(word, data, word_index, last);
	if (token->type == COMMAND || token->type == BUILT_IN)
	{
		if (data->command_flag)
			token->type = ARGUMENT;
		else
			data->command_flag = 1;
	}
	else if (token->type == IN_REDIR || token->type \
		== OUT_REDIR || token->type == HERE_DOC || \
		token->type == APPEND || token->type == PIPE)
		data->command_flag = 0;
	if (last != NULL)
	{
		last->next = token;
		token->prev = last;
	}
	return (token);
}
