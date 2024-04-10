/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:20:23 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 02:46:22 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_built_ins(t_token *args, t_data *data)
{
	char	**cmd_args;

	cmd_args = get_cmd_arg2(args);
	if (ft_strcmp(args->content, "echo") == 0)
		exec_echo(data, args);
	else if (ft_strcmp(args->content, "cd") == 0)
		exec_cd(cmd_args, data);
	else if (ft_strcmp(args->content, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(args->content, "export") == 0)
		exec_export(cmd_args, data);
	else if (ft_strcmp(args->content, "unset") == 0)
		exec_unset(cmd_args, data);
	else if (ft_strcmp(args->content, "env") == 0)
		exec_env(data);
	else if (ft_strcmp(args->content, "exit") == 0)
		exec_exit(args, cmd_args, data);
	else
		ft_perror_arg(args->content, "command not found.\n");
	free_array(cmd_args);
	return ;
}

char	**get_cmd_arg2(t_token *args)
{
	t_token	*arg;
	char	**cmd_args;
	int		i;

	arg = args;
	i = 0;
	while (arg && arg->next && (arg->next->type == ARGUMENT))
	{
		i++;
		arg = arg->next;
	}
	cmd_args = malloc1(sizeof(char *) * (i + 1));
	i = 0;
	arg = args->next;
	while (arg && arg->type == ARGUMENT)
	{
		cmd_args[i] = ft_strdup(arg->content);
		i++;
		arg = arg->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}
