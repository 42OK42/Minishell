/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:22 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/22 17:01:18 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_convert_positive(int len, unsigned int nbr)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = len - 1;
	str[len] = 0;
	if (nbr == 0)
		str[0] = '0';
	else
	{
		while (nbr != 0)
		{
			str[i] = nbr % 10 + 48;
			nbr = nbr / 10;
			i = i - 1;
		}
	}
	return (str);
}

char	*ft_convert_negative(int len, int sign, unsigned int nbr)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (len + sign + 1));
	if (str == NULL)
		return (NULL);
	i = len;
	str[len + 1] = 0;
	while (i > 0)
	{
		str[i] = nbr % 10 + 48;
		nbr = nbr / 10;
		i = i - 1;
	}
	str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int				len;
	int				sign;
	unsigned int	nbr;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	len = ft_len(nbr);
	if (len == 0)
		len = 1;
	if (n < 0)
		str = ft_convert_negative(len, sign, nbr);
	if (n >= 0) 
		str = ft_convert_positive(len, nbr);
	return (str);
}
