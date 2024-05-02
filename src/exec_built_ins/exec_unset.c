/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:49:39 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 00:44:01 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(char **cmd_args, t_data *data)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		var = var_name(data->env[i]);
		j = 0;
		while (cmd_args[j])
		{
			if (ft_strcmp(var, cmd_args[j]) == 0)
			{
				data->env = erase_var(data, data->env[i]);
				i = i - 1;
				break ;
			}
			j++;
		}
		free(var);
		i++;
	}
}

char	**erase_var(t_data *data, char *var)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->env[i])
		i++;
	new = malloc1(sizeof(char *) * i);
	i = 0;
	while (data->env[i])
	{
		if (ft_strcmp(data->env[i], var) != 0)
		{
			new[j] = ft_strdup(data->env[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free_array(data->env);
	return (new);
}

char	*var_name(char *env_name)
{
	int		i;
	char	*var_name;

	i = 0;
	while (env_name[i] && env_name[i] != '=')
		i++;
	var_name = malloc1(i + 1);
	i = 0;
	while (env_name[i] != '=' && env_name[i])
	{
		var_name[i] = env_name[i];
		i++;
	}
	var_name[i] = 0;
	return (var_name);
}
