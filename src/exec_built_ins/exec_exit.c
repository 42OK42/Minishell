/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:40:04 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 02:49:25 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_numeric_argument(char **cmd_args, t_token *args, t_data *data)
{
	ft_perror("exit\n");
	ft_perror_arg_middle("Error: ", cmd_args[0], ": numeric "
		"argument required\n");
	free_array(cmd_args);
	free_all1(args, data);
	exit(2);
}

void	exec_exit(t_token *args, char **cmd_args, t_data *data)
{
	int		j;

	j = 0;
	while (cmd_args[j])
		j++;
	if (cmd_args[0] && ft_onlydigits(cmd_args[0]) == 0)
		non_numeric_argument(cmd_args, args, data);
	if (j > 1)
	{
		ft_perror("minishell: exit: too many arguments");
		data->exit = 1;
	}
	else if ((data->parts == 1) && (j == 0 || ft_strcmp(cmd_args[0], "0") == 0))
	{
		ft_printf("exit\n");
		data->exit = 0;
	}
	else
		exec_exit2(cmd_args, data);
	j = data->exit;
	free_array(cmd_args);
	free_all1(args, data);
	exit (j);
}

void	exec_exit2(char **cmd_args, t_data *data)
{
	long int	status;

	if (!(cmd_args[0]))
	{
		data->exit = 0;
		return ;
	}
	status = ft_atoli(cmd_args[0]);
	if (status != 0)
	{
		if (status <= 255 && status >= 0)
			data->exit = ft_atoi(cmd_args[0]);
		if (status > 255)
			data->exit = modulo(status);
		if (status < 0)
			data->exit = negative((int)status);
	}
	else
		data->exit = 2;
	return ;
}

int	modulo(long int status)
{
	int	i;

	i = status % 256;
	return (i);
}

int	negative(int status)
{
	status = 256 + status;
	return (status);
}
