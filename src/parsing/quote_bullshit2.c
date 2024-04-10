/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_bullshit2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:23:19 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/05 02:52:56 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_word_and_replace(int i, int j, char **words)
{
	size_t	len;
	char	*new_word;

	len = ft_strlen(words[i]);
	new_word = (char *)malloc((len - 1) * sizeof(char));
	if (new_word == NULL)
	{
		printf("Error: Out of memory.\n");
		return ;
	}
	ft_strlcpy(new_word, words[i], j + 1);
	j += 2;
	if ((size_t)j >= len)
		new_word[j] = '\0';
	else
		ft_strlcpy(new_word + j - 2, words[i] + j, len);
	free(words[i]);
	words[i] = new_word;
}

void	remove_empty_quotes(char **words)
{
	int	i;
	int	j;

	i = 0;
	while (words[i])
	{
		j = 0;
		while (words[i][j])
		{
			if (words[i][j] == '\"' && words[i][j + 1] == '\"')
			{
				free_word_and_replace(i, j, words);
				j--;
			}
			if (words[i][j] == '\'' && words[i][j + 1] == '\'')
			{
				free_word_and_replace(i, j, words);
				j--;
			}
			j++;
		}
		i++;
	}
}

int	process_single_quote(char *word, int *result, t_data *data, int word_index)
{
	int	temp;

	data->j2++;
	temp = data->j2;
	while (word[data->j2] != '\'' && word[data->j2])
		data->j2++;
	if (word[data->j2] != '\'')
	{
		ft_perror("Error: Mismatched quotes (NWL1).\n");
		return (-1);
	}
	*result += data->j2 - temp;
	data->quote_flag[word_index] = (int) '\'';
	return (0);
}

int	process_double_quote(char *word, int *result, t_data *data, int word_index)
{
	int	temp;

	data->j2++;
	temp = data->j2;
	while (word[data->j2] != '\"' && word[data->j2])
		data->j2++;
	if (word[data->j2] != '\"')
	{
		ft_perror("Error: Mismatched quotes (NWL2).\n");
		return (-1);
	}
	*result += data->j2 - temp;
	data->quote_flag[word_index] = (int) '\"';
	return (0);
}

int	find_length_new_word(char *word, t_data *data, int word_index)
{
	int	result;

	result = 0;
	data->j2 = 0;
	while (word[data->j2])
	{
		if (word[data->j2] == '\'')
		{
			if (process_single_quote(word, &result, data, word_index) == -1)
				return (-1);
		}
		else if (word[data->j2] == '\"')
		{
			if (process_double_quote(word, &result, data, word_index) == -1)
				return (-1);
		}
		else
			result++;
		data->j2++;
	}
	return (result);
}
