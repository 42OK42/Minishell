/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:26:55 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/04 16:58:27 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(void)
{
	char	wd_path[1024];

	if (getcwd(wd_path, sizeof(wd_path)) != NULL)
	{
		ft_printf("%s\n", wd_path);
		return ;
	}
	ft_perror("error in getting wd_path");
	return ;
}
