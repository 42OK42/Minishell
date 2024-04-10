/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:21:39 by bschmidt          #+#    #+#             */
/*   Updated: 2023/07/19 17:21:40 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

int	ft_nlstrlen(const char *str)
{
	int	counter;

	counter = 0;
	while (*str != 0)
	{
		counter++;
		str++;
	}
	return (counter);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		counter;
	int		i; 

	ptr = malloc(ft_nlstrlen(s1) + ft_nlstrlen(s2) + 1);
	if (!(ptr))
		return (NULL);
	counter = 0;
	i = 0;
	while (s1[i] != 0)
	{
		ptr[counter] = s1[counter];
		i++;
		counter++;
	}
	i = 0;
	while (s2[i] != 0)
		ptr[counter++] = s2[i++];
	ptr[counter] = 0;
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			counter;
	unsigned char	*ptr;

	counter = 0;
	ptr = (unsigned char *)s;
	while (counter < n)
	{
		*ptr = 0;
		ptr++;
		counter++;
	}
	return ;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
	{
		return ((char *)s);
	}
	else
		return ((char *) NULL);
}
