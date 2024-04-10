/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:29:11 by bschmidt          #+#    #+#             */
/*   Updated: 2023/07/09 20:29:12 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_base_len(long int nb)
{
	int		len;

	len = 0;
	if (nb < -9223372036854775807)
		return (16);
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

static void	ft_write_nb(long long int nb, char *base)
{
	if (nb == 0)
	{
		ft_putchar_fd('0', 1);
		return ;
	}
	else if (nb < 0)
	{
		ft_putchar_fd('-', 1);
		nb = -nb;
	}
	if (nb < 16)
	{
		if (nb < 10)
			ft_putchar_fd('0' + nb, 1);
		else
			ft_putchar_fd('A' + nb - 10, 1);
	}
	else
	{
		ft_write_nb(nb / 16, base);
		ft_putchar_fd(base[nb % 16], 1);
	}
}

int	print_upperhexa(long int nb)
{
	int		len;
	char	*base;

	base = "0123456789ABCDEF";
	len = 0;
	len = ft_base_len(nb);
	ft_write_nb(nb, base);
	return (len);
}
