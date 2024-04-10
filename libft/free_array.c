/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:27:44 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/05 15:02:23 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array[i])
	{
		free(array);
		return ;
	}
	while (array[i])
		i++;
	i = i - 1;
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}
