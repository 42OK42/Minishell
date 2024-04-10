/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:05:23 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 03:20:09 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_beginning(t_token *args)
{
	if (args == NULL)
	{
		ft_perror("error in find_beginning");
		return (NULL);
	}
	while (args->prev != NULL)
	{
		args = args->prev;
	}
	return (args);
}
