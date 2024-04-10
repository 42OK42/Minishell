/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:01:54 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/04 19:57:33 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_data *data, t_token *args)
{
	int		i;
	int		newline_flag;
	t_token	*arg;

	arg = args;
	get_echo_args(data, arg);
	newline_flag = 1;
	i = 0;
	while (data->echo_args[i] && isnewlineflag(data->echo_args[i]) == 1)
		i++;
	if (i > 0)
		newline_flag = 0;
	while (data->echo_args[i])
	{
		ft_printf("%s", data->echo_args[i]);
		i++;
		if (data->echo_args[i])
			ft_printf(" ");
	}
	if (newline_flag == 1)
		ft_printf("\n");
	data->exit = 0;
	free_array(data->echo_args);
	return ;
}

void	get_echo_args(t_data *data, t_token *arg)
{
	int		i;
	t_token	*arg2;

	arg2 = arg;
	i = 0;
	while (arg)
	{
		if (arg->type == ARGUMENT && arg->prev && arg->prev->type != IN_REDIR 
			&& arg->prev->type != OUT_REDIR && arg->prev->type != APPEND 
			&& arg->prev->type != HERE_DOC)
			i++;
		arg = arg->next;
	}
	data->echo_args = malloc1(sizeof(char *) * (i + 1));
	fill_array(data, arg2);
}

void	fill_array(t_data *data, t_token *arg2)
{
	int	i;

	i = 0;
	while (arg2)
	{
		if (arg2->type == ARGUMENT && arg2->prev && arg2->prev->type != IN_REDIR
			&& arg2->prev->type != OUT_REDIR && arg2->prev->type != APPEND 
			&& arg2->prev->type != HERE_DOC)
		{
			data->echo_args[i] = ft_strdup(arg2->content);
			i++;
		}
		arg2 = arg2->next;
	}
	data->echo_args[i] = NULL;
}

int	isnewlineflag(char *arg)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(arg);
	if (i < len && arg[i] == '-' && is_only_n(arg) == 1 && arg[i + 1])
		return (1);
	return (0);
}

int	is_only_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' )
		i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}
