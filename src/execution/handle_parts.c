/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:27:24 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/24 21:37:13 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_part(t_token *arg, t_data *data)
{
	data->infile_flag = 0;
	if (data->pipes > 0 && data->part == 1)
		handle_beginning(arg, data);
	else if (data->pipes > 0 && data->part > 1)
	{
		if (pipe(data->fd2) == -1)
		{
			perror("error in execpart2");
			exit (1);
		}
		handle_middle(arg, data);
		close(data->fd2[1]);
		data->fd[0] = data->fd2[0];
	}
	else if (data->pipes == 0 && data->part > 1)
	{
		handle_end(arg, data);
	}
	else
		handle_solo(arg, data);
	data->fd_in = 0;
}
