/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:20:01 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 14:14:39 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_token *args, t_data *data)
{
	char	*cmd;
	char	*cmd_path;

	cmd = ft_strdup(args->content);
	data->cmd_args = get_cmd_args(args, cmd);
	if (cmd[0] != '.' && cmd[0] != '/')
		cmd_path = find_command_path3(data, args->content);
	else
		cmd_path = cmd;
	if (cmd_path == NULL)
	{
		free(cmd);
		free(cmd_path);
		free_array(data->env);
		free_array(data->cmd_args);
		free_array(data->files);
		free_pids(data);
		free(data);
		ft_perror_arg(args->content, ": command not found\n");
		free_middle_list(args);
		exit(127);
	}
	execution(args, cmd_path, data, data->env);
	return ;
}

char	*find_command_path3(t_data *data, char *str)
{
	char	*path;
	char	**paths;
	char	*full_path;

	path = get_env_value(data, "PATH");
	paths = ft_split(path, ':');
	full_path = check_access_and_allocate(paths, str);
	if (full_path)
	{
		free_array(paths);
		return (full_path);
	}
	free_array(paths);
	return (NULL);
}

void	execution(t_token *args, char *cmd_path, t_data *data, char **envp)
{
	if (execve(cmd_path, data->cmd_args, envp) == -1)
	{
		ft_perror_arg(args->content, ": command not found\n");
		free_array(data->env);
		free_array(data->files);
		free_pids(data);
		free_middle_list(args);
		free_array(data->cmd_args);
		free(cmd_path);
		free(data);
		exit (127);
	}
	return ;
}

char	**get_cmd_args(t_token *args, char *cmd)
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
	cmd_args = malloc1(sizeof(char *) * (i + 2));
	cmd_args[0] = ft_strdup(cmd);
	i = 1;
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
