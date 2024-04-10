/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wrong.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:08:11 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/21 17:08:12 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
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

int	ft_find_needed_i(char const *s, char c, int index)
{
	int	comp;
	int	i;

	i = 0;
	comp = 0;
	while (s[i] == c && s[i] != 0)
		i++;
	while (comp != index)
	{
		while (s[i] != c && s[i] != 0)
			i++;
		while (s[i] == c && s[i] != 0)
			i++;
		comp++;
	}
	if (s[i] == 0)
		return (0);
	else
		return (i);
}

char	*free_all(char **array, int index)
{
	if (!array || index < 0)
		return (NULL);
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	return (NULL);
}

char	*ft_fill_array(char const *s, char c, int index, char **array)
{
	int		j;
	int		i;
	int		k;
	char	*array2;

	j = 0;
	i = ft_find_needed_i(s, c, index);
	k = i;
	while (s[k] != 0 && s[k] != c)
	{
		k++;
		j++;
	}
	array2 = malloc(sizeof(char) * (j + 1));
	if (!array2)
		return (free_all(array, index - 1));
	j = 0;
	while (s[i] != 0 && s[i] != c)
	{
		array2[j] = s[i];
		j++;
		i++;
	}
	array2[j] = 0;
	return (array2);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	int		words;
	char	**array;

	index = 0;
	words = ft_count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array || !s)
		return (NULL);
	while (index < words)
	{
		array[index] = ft_fill_array(s, c, index, array);
		if (array[index] == NULL)
		{
			free(array);
			return (NULL);
		}
		index++;
	}
	array[index] = 0;
	return (array);
}
