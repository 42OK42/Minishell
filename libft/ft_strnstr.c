/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:54:24 by bschmidt          #+#    #+#             */
/*   Updated: 2023/05/26 17:54:26 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	counter;
	size_t	counter2;

	counter = 0;
	if (*little == 0 || little == NULL)
		return ((char *)big);
	while (big[counter] != 0 && counter < len)
	{
		counter2 = 0;
		while (little[counter2] == big[counter + counter2]
			&& counter + counter2 < len)
		{
			if (little[counter2 + 1] == 0)
				return ((char *)big + counter);
			counter2++;
		}
		counter++;
	}
	return (NULL);
}
