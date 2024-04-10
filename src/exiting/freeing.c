/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:49:25 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/03 13:51:53 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_next_input(t_token *args, t_data *data)
{
	free_list(args);
	free_pids(data);
	free_array(data->files);
}

void	free_data(t_data *data)
{
	free_array(data->env);
	free_quote_flag(data);
	free(data);
}

void	free_all1(t_token *args, t_data *data)
{
	free_middle_list(args);
	free_pids(data);
	free_array(data->files);
	free_data(data);
}

void	free_child(t_data *data, t_token *arg)
{
	//ft_printf("TEST\n");
	free_array(data->env);
	free_array(data->files);
	free_middle_list(arg);
	free_pids(data);
	free(data);
	exit (0);
}
