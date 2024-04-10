/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:01:20 by bschmidt          #+#    #+#             */
/*   Updated: 2023/07/09 20:57:48 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_percent(int len)
{
	ft_putchar_fd('%', 1);
	return (len);
}

static int	ft_no_format(const char *format, int *no_format)
{
	int	k;

	k = 0;
	ft_putchar_fd('%', 1);
	while (format[k] != 0)
	{
		ft_putchar_fd(format[k], 1);
		k++;
	}
	*no_format = 1;
	return (k + 1);
}

static int	use_format(const char *format, va_list arg,
			int count, int *no_format)
{
	if (*format == 0)
		return (0);
	if (*format == 'c')
		return (count += print_c(va_arg(arg, int)));
	if (*format == 's')
		return (count += print_string(va_arg(arg, char *)));
	if (*format == 'p')
		return (count += print_p((unsigned long int)va_arg(arg, void *)));
	if (*format == 'd' || *format == 'i')
		return (count += print_int(va_arg(arg, int)));
	if (*format == 'u')
		return (count += print_uint(va_arg(arg, unsigned int)));
	if (*format == 'x')
		return (count += print_lowerhexa(va_arg(arg, unsigned int)));
	if (*format == 'X')
		return (count += print_upperhexa(va_arg(arg, unsigned int)));
	if (*format == '%')
		return (count += print_percent(1));
	return (count += ft_no_format(format, no_format));
}

int	call_format(const char *format, va_list arg)
{
	int	count;
	int	no_format;

	count = 0;
	no_format = 0;
	while (*format != 0)
	{
		if (*format == '%')
		{
			format++;
			count = use_format(format, arg, count, &no_format);
			if (no_format)
				return (count);
		}
		else
		{
			count += print_c((char) *format);
		}
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;

	va_start (arg, format);
	if (format == NULL)
		return (-1);
	va_end(arg);
	return (call_format(format, arg));
}
