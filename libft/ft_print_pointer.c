/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:27:57 by bschmidt          #+#    #+#             */
/*   Updated: 2023/07/10 22:15:32 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static int	ft_base_len(unsigned long int nb)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

static void	ft_write_nb(unsigned long int nb, char *base)
{
	if (nb == 0)
	{
		ft_putchar_fd('0', 1);
		return ;
	}
	if (nb < 16)
	{
		if (nb < 10)
			ft_putchar_fd('0' + nb, 1);
		else
			ft_putchar_fd('a' + nb - 10, 1);
	}
	else
	{
		ft_write_nb(nb / 16, base);
		ft_putchar_fd(base[nb % 16], 1);
	}
}

int	print_p(unsigned long int ptr)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	count = 0; 
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	count = 2;
	ft_putstr_fd("0x", 1);
	ft_write_nb(ptr, base);
	count += ft_base_len(ptr);
	return (count);
}
