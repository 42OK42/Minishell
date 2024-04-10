/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:02:25 by bschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 12:02:26 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;
	size_t	srcsize;
	size_t	i;

	i = 0;
	dstsize = ft_strlen(dst);
	srcsize = ft_strlen(src);
	if (size <= dstsize)
	{
		return (srcsize + size);
	}
	while (src[i] != 0 && dstsize + i + 1 < size)
	{
		dst[dstsize + i] = src[i];
		i++;
	}
	dst[dstsize + i] = 0;
	return (dstsize + srcsize);
}
