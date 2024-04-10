/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:36:55 by bschmidt          #+#    #+#             */
/*   Updated: 2024/02/25 21:33:33 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_extend_array(char **array, int add)
{
	char	**new;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new = malloc(sizeof(char *) * (i + add + 1));
	new[0] = NULL;
	i = 0;
	while (array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i + add] = NULL;
	free_array(array);
	return (new);
}
