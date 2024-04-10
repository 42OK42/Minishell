/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 02:31:07 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/01 23:43:18 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_here_doc(const char *filename)
{
	if (access(filename, F_OK) != -1) 
	{
		if (unlink(filename) == -1) 
		{
			perror("Error deleting file");
			return ;
		}
		return ;
	}
	else
		return ;
}

void	free_middle_list(t_token *args)
{
	if (!args)
		return ;
	while (args->prev != NULL)
		args = args->prev;
	free_list(args);
}

void	free_list(t_token *args)
{
	t_token	*tmp;

	while (args != NULL)
	{
		tmp = args->next;
		free(args->content);
		free(args);
		args = tmp;
	}
}

void	free_pids(t_data *data)
{
	free(data->pids);
	data->pids = NULL;
}

void	free_quote_flag(t_data *data)
{
	free(data->quote_flag);
	data->quote_flag = NULL;
}
