/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:44:45 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/24 14:44:47 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		counter;
	int		i; 

	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(ptr))
		return (NULL);
	counter = 0;
	i = 0;
	while (s1[i] != 0)
	{
		ptr[counter] = s1[counter];
		i++;
		counter++;
	}
	i = 0;
	while (s2[i] != 0)
		ptr[counter++] = s2[i++];
	ptr[counter] = 0;
	return (ptr);
}
