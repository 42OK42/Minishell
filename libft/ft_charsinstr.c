/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charsinstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:33:06 by bschmidt          #+#    #+#             */
/*   Updated: 2024/01/16 21:39:29 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charsinstr(char *str, char *check)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (check[j])
		{
			if (str[i] == check[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
