/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:35:17 by bschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 17:35:18 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			counter;
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	dest_ptr = dest;
	src_ptr = (unsigned char *)src;
	counter = 0;
	if (dest_ptr >= src_ptr && dest_ptr < src_ptr + n)
	{
		return (NULL);
	}
	while (counter < n)
	{
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src_ptr++;
		counter++;
	}
	return (dest);
}
