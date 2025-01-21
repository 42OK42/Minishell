/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:42:38 by bschmidt          #+#    #+#             */
/*   Updated: 2024/01/18 20:43:09 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_argument(t_token *arg, t_data *data)
{
	exec_argument2(arg, data);
	return ;
}

void	exec_argument2(t_token *arg, t_data *data)
{
	char	*cmd_path;
	char	**cmd_args;

	if (ft_strcmp(arg->content, "./minishell") == 0)
		increase_sh_level(data);
	cmd_path = get_cmd_path(arg, data);
	cmd_args = get_right_args(arg);
	if (execve(cmd_path, cmd_args, data->env) == -1)
	{
		ft_perror_arg(arg->content, ": command not found\n");
		free_array(cmd_args);
		free(cmd_path);
		free_array(data->env);
		free(data->files);
		free_pids(data);
		free(data);
		free_middle_list(arg);
		exit (127);
	}
}

char	**get_right_args(t_token *args)
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
	i = 0;
	arg = args;
	while (arg && arg->type == ARGUMENT)
	{
		cmd_args[i] = ft_strdup(arg->content);
		i++;
		arg = arg->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

char	*get_cmd_path(t_token *arg, t_data *data)
{
	char	*name;
	char	*pwd;
	char	*cmd_path;

	name = arg->content;
	if (name[0] == '/' || ft_strncmp(name, "../", 3) == 0)
		return (ft_strdup(name));
	data->env_value = get_env_value(data, "PWD");
	pwd = ft_strjoin(data->env_value, "/");
	cmd_path = ft_strjoin(pwd, name);
	free(data->env_value);
	free(pwd);
	return (cmd_path);
}

void	increase_sh_level(t_data *data)
{
	int		sh_lvl;
	char	*str_sh_lvl;
	char	*var_delete;
	char	*var_add;

	var_delete = "SHLVL";
	data->env_value = get_env_value(data, "SHLVL");
	sh_lvl = ft_atoi(data->env_value);
	if (sh_lvl == 0)
	{
		ft_perror("Could not fetch sh_lvl\n");
		exit (1);
	}
	sh_lvl = sh_lvl + 1;
	str_sh_lvl = ft_itoa(sh_lvl);
	var_add = ft_strjoin("SHLVL=", str_sh_lvl);
	free(data->env_value);
	free(str_sh_lvl);
	replace_in_env(var_delete, var_add, data);
}
