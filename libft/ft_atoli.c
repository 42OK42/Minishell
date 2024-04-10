/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:54:30 by bschmidt          #+#    #+#             */
/*   Updated: 2024/03/04 16:46:36 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_signcheck(const char *str)
{
	int	j;
	int	minus_counter;

	minus_counter = 0;
	j = 0;
	while ((str[j] != 0 && str[j] > 57) || str[j] < 48)
	{
		if (str[j] == 45)
		{
			minus_counter++;
		}
		j++;
	}
	return (minus_counter);
}

long int	ft_startatoli(const char *str, int i)
{
	long int	output;

	output = 0;
	while (str[i] <= 57 && str[i] >= 48)
	{
		output = output * 10 + str[i] - 48;
		i++;
	}
	if (ft_signcheck(str) % 2 == 1)
	{
		output = output * (-1);
	}
	return (output);
}

long int	ft_atoli(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\t')
	{
		i++;
	}
	if (str[i] == 43 || str[i] == 45)
	{
		i++;
	}
	if (ft_isdigit(str[i]) == 0)
		return (0);
	return (ft_startatoli(str, i));
}
