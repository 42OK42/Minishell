/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:22:11 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/25 14:42:34 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_length_var(char *line, int i)
{
	int	start;

	start = i;
	while (line[i] != ' ' && line[i] != '\0' && line[i] != '$' \
		&& line[i] != '\"' && line[i] != '\'' && line[i] != '/' \
			&& line[i] != ':')
		i++;
	return (i - start);
}

void	fetch_env_value(t_data *data, char *line, int i, int len_var)
{
	char	*var_name;

	var_name = malloc1(sizeof(char) * len_var + 1);
	ft_strlcpy(var_name, &line[i], len_var + 1);
	data->env_value = get_env_value1(data, var_name);
	if (data->env_value == NULL)
		data->env_value = ft_strdup("");
	data->env_len = ft_strlen(data->env_value);
	if (data->env_len == 0)
		data->env_len++;
	free(var_name);
}

char	*actually_expand(t_data *data, char *line, int i)
{
	char	*result;
	int		len_var;

	data->i = i++;
	if (line[i] == '?')
	{
		data->env_value = ft_itoa(data->exit);
		data->env_len = ft_strlen(data->env_value);
		len_var = 1;
	}
	else
	{
		len_var = find_length_var(line, i);
		fetch_env_value(data, line, i, len_var);
	}
	data->len = ft_strlen(line);
	result = malloc1(sizeof(char) * (data->len - \
		(len_var + 1)) + data->env_len + 1);
	ft_memcpy(result, line, data->i);
	ft_memcpy(&result[data->i], data->env_value, data->env_len);
	ft_strlcpy(&result[data->i + data->env_len], \
		&line[i + len_var], data->len - i);
	if (*data->env_value)
		free(data->env_value);
	return (free(line), result);
}

int	line_only_spaces(char	*line, int i)
{
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && \
			line[i] != '\v' && line[i] != '\f' && line[i] != '\r' && \
				line[i] != '\'' && line[i] != '\"')
			return (-1);
		i++;
	}
	return (1);
}

int	count_dollar_pairs(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '$' && *(s + 1) == '$')
		{
			count++;
			s += 2;
		}
		else
			s++;
	}
	return (count);
}
