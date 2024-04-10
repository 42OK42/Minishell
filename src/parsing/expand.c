/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:14:05 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/03 22:22:27 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_double_dollar(char *line)
{
	int		size;
	char	*new_line;
	char	*p;

	size = strlen(line) - (2 * count_dollar_pairs(line)) + 1;
	new_line = malloc(size * sizeof(char));
	p = new_line;
	while (*line)
	{
		if (*line == '$' && *(line + 1) == '$')
			line += 2;
		else
			*p++ = *line++;
	}
	*p = '\0';
	return (new_line);
}

void	update_quote_flags(int *single_q, int *double_q, char c)
{
	if (c == '\'')
	{
		if (*single_q == 0 && *double_q == 0)
			*single_q = 1;
		else
		{
			*single_q = 0;
			if (*double_q == 1)
				*double_q = 0;
		}
	}
	if (c == '\"')
	{
		if (*double_q == 0)
			*double_q = 1;
		else
		{
			*double_q = 0;
			if (*single_q == 1)
				*single_q = 0;
		}
	}
}

char	*process_dollar_expansion(char *line, t_data *data, int *i)
{
	char	*old_line;

	old_line = line;
	if (line[*i + 1] == '$')
	{
		line = replace_double_dollar(line);
		free(old_line);
	}
	if (line[*i] == '$')
	{
		if (line[*i + 1] != '$' && line_only_spaces(line, *i + 1) == -1)
			line = actually_expand(data, line, *i);
	}
	return (line);
}

char	*expand(char *line, t_data *data)
{
	int		i;
	int		double_q;
	int		single_q;
	char	*old_line;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (line[i])
	{
		update_quote_flags(&single_q, &double_q, line[i]);
		if (line[i] == '$' && single_q == 0)
		{
			old_line = line;
			line = process_dollar_expansion(line, data, &i);
			if (old_line != line)
				continue ;
		}
		i++;
	}
	return (line);
}

int	find_dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
