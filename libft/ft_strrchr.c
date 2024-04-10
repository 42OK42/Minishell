/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>      +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:30 by bschmidt          #+#    #+#             */
/*   Updated: 2023/05/26 14:28:32 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*adress;

	adress = NULL;
	while (*s != 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			adress = (char *)s;
		}
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		adress = (char *)s;
	return (adress);
}
