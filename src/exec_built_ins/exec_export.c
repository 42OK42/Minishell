/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:41:22 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 02:56:33 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_or_add_env_var(char *cmd_arg, t_data *data)
{
	char	*var_delete;
	int		j;

	j = 0;
	if (var_in_env(cmd_arg, data) == 1)
	{
		var_delete = var_name(cmd_arg);
		replace_in_env(var_delete, cmd_arg, data);
		free(var_delete);
	}
	else 
	{
		while (data->env[j])
			j++;
		data->env = ft_extend_array(data->env, 1);
		data->env[j] = ft_strdup(cmd_arg);
	}
}

void	exec_export(char **cmd_args, t_data *data)
{
	int	i;

	i = 0;
	if (cmd_args[i] == NULL) 
	{
		empty_export(data);
		return ;
	}
	while (cmd_args[i]) 
	{
		if (cmd_check(cmd_args[i]) == 1)
			replace_or_add_env_var(cmd_args[i], data);
		i++;
	}
}

int	var_in_env(char	*str, t_data *data)
{
	int		i;
	char	*str1;
	char	*var;

	str1 = var_name(str);
	i = 0;
	while (data->env[i])
	{
		var = var_name(data->env[i]);
		if (ft_strcmp(str1, var) == 0)
		{
			free(var);
			free(str1);
			return (1);
		}
		free(var);
		i++;
	}
	free(str1);
	return (0);
}

int	check_variable_name(char *cmd, char *disallowed_chars)
{
	int		i;
	char	*var_name;

	i = 0;
	if (cmd[i] && cmd[i] == '=')
		return (ft_perror("start with = not allowed\n"), 0);
	while (cmd[i] && cmd[i] != '=')
		i++;
	var_name = malloc1(sizeof(char) * i + 1);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		var_name[i] = cmd[i];
		i++;
	}
	var_name[i] = 0;
	if (ft_charsinstr(var_name, disallowed_chars) == 1)
	{
		free(var_name);
		return (0);
	}
	free(var_name);
	return (1);
}

void	empty_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_printf("declare -x %s\n", data->env[i]);
		i++;
	}
}
