/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:37 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 02:56:09 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strcmp(env[i], data->env[i]) == 0)
			i++;
		else
			ft_printf("not equal");
	}
}

void	print_args(t_token *args)
{
	while (args != NULL)
	{
		if ((args->type) == ARGUMENT)
			ft_printf("Its an Argument\n Mit Content: %s\n", args->content);
		if ((args->type) == IN_REDIR)
			ft_printf("Its an in_redir\n");
		if ((args->type) == OUT_REDIR)
			ft_printf("Its an out_redir\n");
		if ((args->type) == HERE_DOC)
			ft_printf("Its a Here_Doc\n");
		if ((args->type) == APPEND)
			ft_printf("Its an Append\n");
		if ((args->type) == PIPE)
			ft_printf("Its a Pipe\n");
		if ((args->type) == COMMAND)
			ft_printf("Its a Command\n");
		if ((args->type) == BUILT_IN)
			ft_printf("Its a Built_in\n");
		args = args->next;
	}
}

void	print_struct(t_data *data)
{
	ft_printf("closed: %d\n", data->closed);
	ft_printf("here_doc: %d\n", data->here_doc);
	ft_printf("hd_flag: %d\n", data->hd_flag);
	ft_printf("saved_stdin: %d\n", data->saved_stdin);
	ft_printf("saved_stdout: %d\n", data->saved_stdout);
	ft_printf("parts: %d\n", data->parts);
	ft_printf("part: %d\n", data->part);
	ft_printf("in_dirs: %d\n", data->in_dirs);
	ft_printf("out_dirs: %d\n", data->out_dirs);
	ft_printf("fd_in: %d\n", data->fd_in);
	ft_printf("fd_out: %d\n", data->fd_out);
}

	/* int		test;
	int		exit;
	int		args;
	int		cmds;
	int		x;
	int		solo;
	int		built_ins;
	int		fd[2];
	int		fd2[2];
	pid_t	*pids; */
