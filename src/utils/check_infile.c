/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:21:16 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 02:53:03 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_infile(t_data *data, char *filename)
{
	int	i;

	i = 0;
	if (access(filename, F_OK) == 0)
	{
		return ;
	}
	else
	{
		data->files = ft_extend_array(data->files, 1);
		while (data->files[i])
			i++;
		data->files[i] = ft_strdup(filename);
		return ;
	}
}

void	check_infile(t_data *data, char *filename)
{
	int	i;

	i = 0;
	while (data->files[i] != NULL && ft_strcmp(data->files[i], filename) != 0)
	{
		i++;
	}
	if (data->files[i] && ft_strcmp(data->files[i], filename) == 0)
	{
		ft_perror("Error: infile wasnt created yet\n");
		data->infile_flag = 1;
		return ;
	}
	else
		return ;
}
