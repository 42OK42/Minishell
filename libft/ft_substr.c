/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:44:55 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/25 16:35:06 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	counter;

	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	ptr = malloc((len * sizeof(char)) + 1);
	if (ptr == NULL)
		return (NULL);
	counter = 0;
	while (counter < len)
	{
		ptr[counter] = s[start + counter];
		counter++;
	}
	ptr[counter] = 0;
	return (ptr);
}
