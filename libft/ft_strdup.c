/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:45:08 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/24 14:45:09 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		counter;

	counter = 0;
	ptr = malloc((sizeof(char) * ft_strlen(s1)) + 1);
	if (!ptr)
		return (NULL);
	while (s1[counter] != 0)
	{
		ptr[counter] = s1[counter];
		counter++;
	}
	ptr[counter] = 0;
	return (ptr);
}
