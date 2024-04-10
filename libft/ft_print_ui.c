/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:35:54 by bschmidt          #+#    #+#             */
/*   Updated: 2023/07/09 20:35:54 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putuinbr(unsigned int nb)
{
	if (nb == 0)
	{
		ft_putchar_fd('0', 1);
		return ;
	}
	if (nb > 0 && nb < 10)
		ft_putchar_fd(nb + 48, 1);
	else
	{
		ft_putuinbr(nb / 10);
		ft_putchar_fd(nb % 10 + 48, 1);
	}
}

int	print_uint(unsigned int ui)
{
	int	len;

	ft_putuinbr(ui);
	len = 0;
	if (ui == 0)
		return (1);
	while (ui > 0)
	{
		ui = ui / 10;
		len++;
	}
	return (len);
}
