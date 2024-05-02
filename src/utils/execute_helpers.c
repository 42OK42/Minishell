/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:33:40 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 00:18:55 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_perror("forking failed");
		return (-1);
	}
	return (pid);
}

char	*get_env_value2(t_data *data, char *str)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (data->env[i])
	{
		var = var_name(data->env[i]);
		if (ft_strcmp(var, str) == 0)
		{
			value = trim_strfront(data->env[i], ft_strlen(var) + 1);
			free(var);
			return (value);
		}
		else
		{
			free(var);
			i++;
		}
	}
	return (NULL);
}

char	*trim_strfront(char *str, int x)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	new_str = malloc1(sizeof(char) * (i + 1 - x));
	i = x;
	while (str[i])
	{
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j] = 0;
	return (new_str);
}

char	*get_env_value(t_data *data, char *str)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (data->env[i])
	{
		var = var_name(data->env[i]);
		if (ft_strcmp(var, str) == 0)
		{
			value = trim_strfront(data->env[i], ft_strlen(var) + 1);
			free(var);
			return (value);
		}
		else
		{
			free(var);
			i++;
		}
	}
	return ("0");
}

char	*get_env_value1(t_data *data, char *str)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (data->env[i])
	{
		var = var_name(data->env[i]);
		if (ft_strcmp(var, str) == 0)
		{
			value = trim_strfront(data->env[i], ft_strlen(var) + 1);
			free(var);
			return (value);
		}
		else
		{
			free(var);
			i++;
		}
	}
	return ("");
}
