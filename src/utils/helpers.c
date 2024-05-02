/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:09:06 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/24 21:31:59 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	ft_perror_arg(char *str1, char *str2)
{
	int		i;
	char	*print;

	print = ft_strjoin(str1, str2);
	i = 0;
	while (print[i])
	{
		write(2, &print[i], 1);
		i++;
	}
	free(print);
}

void	ft_perror_arg_middle(char *str1, char *str2, char *str3)
{
	char	*msg1;
	char	*msg2;
	int		i;

	i = 0;
	msg1 = ft_strjoin(str1, str2);
	msg2 = ft_strjoin(msg1, str3);
	while (msg2[i])
	{
		write(2, &msg2[i], 1);
		i++;
	}
	free(msg1);
	free(msg2);
}

void	counting_redirs(t_token *arg, t_data *data)
{
	t_token	*args;

	args = arg;
	data->in_dirs = 0;
	data->out_dirs = 0;
	while (arg && arg->type != PIPE)
	{
		if (arg->type == HD_PREP)
			data->here_doc++;
		if (arg->type == IN_REDIR || arg->type == HD_PREP)
			data->in_dirs++;
		if (arg->type == OUT_REDIR || arg->type == APPEND)
			data->out_dirs++;
		arg = arg->next;
	}
	find_input(args, data);
}

void	find_input(t_token *arg, t_data *data)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (arg && arg->type != PIPE)
	{
		if (arg->type == IN_REDIR || arg->type == HD_PREP)
			i++;
		if (i == data->in_dirs)
		{
			if (arg->type == HD_PREP)
			{
				data->hd_flag = 1;
				return ;
			}
			else
			{
				data->hd_flag = 0;
				return ;
			}
		}
		arg = arg->next;
	}
}
