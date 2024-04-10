/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:10:07 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 02:47:26 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd2(char **cmd_args, char *old_wd, t_data *data)
{
	char	*wd;
	char	*var_add1;
	char	*var_add2;

	if (chdir(cmd_args[0]) == 0)
	{
		wd = get_wd();
		var_add1 = ft_strjoin("PWD=", wd);
		var_add2 = ft_strjoin("OLDPWD=", old_wd);
		replace_in_env("PWD", var_add1, data);
		replace_in_env("OLDPWD", var_add2, data);
		free(var_add1);
		free(var_add2);
		free(wd);
	}
	else
		ft_perror("Failed changing directory.\n");
}

void	exec_cd(char **cmd_args, t_data *data)
{
	char	*old_pwd;

	old_pwd = get_env_value(data, "PWD");
	if (old_pwd == NULL)
	{
		ft_perror("Could not get old working directory.\n");
		return ;
	}
	if (cmd_args[0] == NULL)
		cdhome(data, old_pwd);
	else
		exec_cd2(cmd_args, old_pwd, data);
	free(old_pwd);
}

void	cdhome(t_data *data, char *old_pwd)
{
	char	*home;
	char	*var_add1;
	char	*var_add2;

	home = get_env_value(data, "HOME");
	var_add1 = ft_strjoin("PWD=", home);
	var_add2 = ft_strjoin("OLDPWD=", old_pwd);
	if (home)
	{
		if (chdir(home) == 0)
		{
			replace_in_env("PWD", var_add1, data);
			replace_in_env("OLDPWD", var_add2, data);
			free(var_add1);
			free(var_add2);
		}
		else
			ft_perror("Could not change into home directory.\n");
	}
	else
		ft_perror("Couldn't get home variable.\n");
	free(home);
}

char	*get_wd(void)
{
	char	*wd;

	wd = malloc(PATH_MAX);
	if (wd == NULL)
	{
		perror("malloc() error");
		return (NULL);
	}
	if (getcwd(wd, PATH_MAX) == NULL)
	{
		perror("getcwd() error");
		free(wd);
		return (NULL);
	}
	return (wd);
}
