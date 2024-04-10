/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:34:39 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 15:37:48 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_variable_to_replace(char *var_delete, t_data *data)
{
	int		i;
	char	*var;
	int		found;

	found = 0;
	i = 0;
	while (data->env[i])
	{
		var = var_name(data->env[i]);
		if (ft_strcmp(var, var_delete) == 0) 
		{
			free(data->env[i]);
			free(var);
			found = 1;
			break ;
		}
		free(var);
		i++;
	}
	if (found == 1)
		return (i);
	else
		return (-1);
}

void	replace_variable_in_env(int index, char *var_add, t_data *data)
{
	if (index >= 0) 
		data->env[index] = ft_strdup(var_add);
	else
	{
		ft_perror("couldnt find variable to replace.\n");
		data->exit = 1;
	}
}

void	replace_in_env(char *var_delete, char *var_add, t_data *data)
{
	int	index;

	index = find_variable_to_replace(var_delete, data);
	replace_variable_in_env(index, var_add, data);
}

int	cmd_check(char *cmd_arg)
{
	char	*disallowed_chars;

	disallowed_chars = "=!@#$%^&*()-+[]{};:'\",<.>/?|`~ \\";
	if (cmd_arg[0] >= 48 && cmd_arg[0] <= 57)
	{
		ft_perror("export variable cant begin with number\n");
		return (0);
	}
	else if (check_variable_name(cmd_arg, disallowed_chars) == 0)
	{
		if (cmd_arg[0] != '=')
			ft_perror("Forbidden chars in the variable name found.\n");
		return (0);
	}
	else if (check_variable(cmd_arg) == 0)
	{
		ft_perror("invalid variable. Use like this: a=1.\n");
		return (0);
	}
	return (1);
}

int	check_variable(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != '=')
	{
		return (0);
	}
	return (1);
}
