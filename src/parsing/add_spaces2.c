/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:21:13 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/05 03:10:06 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

int	count_special_char_sequence(const char *s, int *i, char target_char)
{
	int	count;
	int	special_char_count;

	count = 0;
	special_char_count = 0;
	while (s[*i] == target_char)
	{
		special_char_count++;
		if (special_char_count == 2)
		{
			count++;
			special_char_count = 0;
		}
		(*i)++;
	}
	if (s[*i] != '\0' && special_char_count == 1)
		count++;
	return (count);
}

int	count_pipe_characters(const char *s, int *i)
{
	int	count;

	count = 0;
	while (s[*i] == '|')
	{
		count++;
		(*i)++;
	}
	return (count);
}

int	count_additional_spaces(const char *s, int seq_count)
{
	int		i;
	int		count;
	int		single_q;
	int		double_q;
	char	current_char;

	i = 0;
	count = 0;
	single_q = 0;
	double_q = 0;
	while (s[i] != '\0')
	{
		seq_count = 0;
		current_char = s[i];
		update_quote_flags(&single_q, &double_q, s[i]);
		if ((s[i] == '<' || s[i] == '>' || s[i] == '|') \
			&& single_q == 0 && double_q == 0)
		{
			while (s[i] == current_char)
			{
				seq_count++;
				i++;
			}
			if (seq_count == 1)
				count += 2;
			else if (seq_count == 2)
				count += 1;
			else
				count += 1 + (seq_count - 2) * 2;
			if (s[i] != ' ' && s[i] != '\0')
				count++;
		}
		else
		{
			i++;
		}
	}
	return (count);
}

void	handle_special_char(t_space_info *info, char *s, char c)
{
	if (info->j > 0 && (info->new_str)[info->j - 1] != ' ')
		(info->new_str)[info->j++] = ' ';
	while (s[info->i] == c)
	{
		(info->new_str)[info->j++] = s[info->i++];
		(info->special_char_count)++;
		if (info->special_char_count == 2 || s[info->i] != c)
		{
			if (s[info->i] != ' ')
				(info->new_str)[info->j++] = ' ';
			info->special_char_count = 0;
		}
	}
}
