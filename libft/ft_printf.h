/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:46:51 by bschmidt          #+#    #+#             */
/*   Updated: 2023/07/09 21:05:53 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

void	ft_putchar_fd(char c, int fd);
int		ft_printf(const char *format, ...);
int		print_c(char c);
int		print_lowerhexa(long int nb);
int		print_upperhexa(long int nb);
int		print_int(int nb);
int		print_p(unsigned long int ptr);
int		print_string(char *s);
int		print_uint(unsigned int ui);

#endif // FT_PRINTF_H
