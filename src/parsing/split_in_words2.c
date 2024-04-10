/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_words2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:26:39 by okrahl            #+#    #+#             */
/*   Updated: 2024/02/29 17:26:44 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && in_word)
			in_word = 0;
		s++;
	}
	return (count);
}

void	assign_word(char **result, int word_index, \
char const *start, int length)
{
	result[word_index] = (char *)malloc((length + 1) * sizeof(char));
	if (result[word_index] == NULL)
		return ;
	ft_strncpy(result[word_index], start, length);
	result[word_index][length] = '\0';
}

int	is_enclosed_in_quotes(char const *start, int length, char quote)
{
	return (length >= 2 && start[0] == quote && start[length - 1] == quote);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_count_words10(char const *s, char c)
{
	int	words;
	int	delimiter_on;
	int	i;

	i = 0;
	words = 0;
	delimiter_on = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && delimiter_on == 0)
		{
			words++;
			delimiter_on = 1;
		}
		if (s[i] == c)
		{
			delimiter_on = 0;
		}
		i++;
	}
	return (words);
}
