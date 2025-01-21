/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:10:05 by okrahl            #+#    #+#             */
/*   Updated: 2024/02/29 17:31:05 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_allocated_memory(char **array, int index)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
}

char	*handle_quotes(const char *s, char c, t_data *data, char *current_quote)
{
	data->i = data->j;
	while (s[data->j] && (s[data->j] != c || \
		(s[data->j] == c && *current_quote != 0)))
	{
		if (s[data->j] == '\'' || s[data->j] == '\"')
		{
			if (*current_quote == 0)
				*current_quote = s[data->j];
			else if (*current_quote == s[data->j])
				*current_quote = 0;
		}
		(data->j)++;
	}
	return (ft_strndup(&s[data->i], data->j - data->i));
}

static char	**initialize_split(char const *s, char c, t_data *data, int *words)
{
	char	**array;
	int		i;

	*words = ft_count_words10(s, c);
	data->quote_flag = malloc(*words * sizeof(int));
	if (!data->quote_flag)
		return (NULL);
	i = 0;
	while (i < *words)
	{
		data->quote_flag[i] = 0;
		i++;
	}
	array = malloc(sizeof(char *) * (*words + 1));
	if (!array)
	{
		free(data->quote_flag);
		return (NULL);
	}
	return (array);
}

static char	**perform_split(char const *s, char c, t_data *data, char **array)
{
	char	current_quote;
	int		i;

	i = 0;
	current_quote = 0;
	while (s[data->j])
	{
		array[i] = handle_quotes(s, c, data, &current_quote);
		if (!array[i])
		{
			free_allocated_memory(array, i);
			free(data->quote_flag);
			return (NULL);
		}
		i++;
		while (s[data->j] == c)
			(data->j)++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split_modified(char const *s, char c, t_data *data)
{
	int		words;
	char	**array;

	if (!s)
		return (NULL);
	array = initialize_split(s, c, data, &words);
	if (!array)
		return (NULL);
	data->j = 0;
	data->index1 = 0;
	return (perform_split(s, c, data, array));
}
