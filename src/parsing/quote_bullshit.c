/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_bullshit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:12:52 by okrahl            #+#    #+#             */
/*   Updated: 2024/02/29 17:30:48 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quotes(char *word, char *new_word, t_data *data, int *nwi)
{
	while (word[data->j2])
	{
		if (word[data->j2] == '\'' || word[data->j2] == '\"')
		{
			if (data->current_quote == 0)
				data->current_quote = word[data->j2];
			else if (data->current_quote == word[data->j2])
				data->current_quote = 0;
			else
				new_word[(*nwi)++] = word[data->j2];
			data->j2++;
		}
		else
			new_word[(*nwi)++] = word[data->j2++];
	}
}

char	*create_new_word(char *word, t_data *data, \
	int word_index, int length_new_word)
{
	int		nwi;
	char	*new_word;

	data->current_quote = 0;
	new_word = malloc1((length_new_word + 1) * sizeof(char));
	new_word[length_new_word] = '\0';
	data->j2 = 0;
	nwi = 0;
	process_quotes(word, new_word, data, &nwi);
	if (data->current_quote != 0)
		data->quote_flag[word_index] = (int)data->current_quote;
	return (new_word);
}

char	*update_word(char *word, t_data *data, int word_index)
{
	int		length_new_word;
	char	*new_word;

	new_word = NULL;
	length_new_word = find_length_new_word(word, data, word_index);
	if (length_new_word == -1)
		return (NULL);
	new_word = create_new_word(word, data, word_index, length_new_word);
	return (new_word);
}

int	quote_bullshit(char **words, t_data *data)
{
	int		i;
	char	*new_word;

	i = 0;
	while (words[i] != NULL)
	{
		new_word = update_word(words[i], data, i);
		if (new_word == NULL)
			return (0);
		free(words[i]);
		words[i] = new_word;
		i++;
	}
	return (1);
}
