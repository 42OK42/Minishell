/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:30:31 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/21 11:30:33 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != 0 && ft_strchr(set, s1[i]) != NULL)
	{
		i++;
	}
	return (i);
}

int	ft_getend(char const *s1, char const *set)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = ft_strlen(s1);
	j = len - 1;
	while (len - i > 0 && ft_strchr(set, s1[j]) != NULL)
	{
		i++;
		j--;
	}
	return (j);
}

char	*ft_dupstring(char const *s1, char const *set)
{
	int		i;
	char	*newstring;
	int		start;
	int		end;

	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	i = 0;
	newstring = malloc(sizeof(char) * end - start + 2);
	while (s1[i] != 0)
	{
		newstring[i] = s1[i];
		i++;
	}
	return (newstring);
}

char	*ft_createstring(char const *s1, char const *set)
{
	char	*newstring;
	int		start;
	int		end;

	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	newstring = malloc(sizeof(char) * (end - start + 2));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, s1 + start, end - start + 2);
	return (newstring);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstring;
	int		start;
	int		end;

	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
		newstring = ft_dupstring(s1, set);
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (end < start)
	{
		newstring = malloc(sizeof(char) * 1);
		if (newstring == NULL)
			return (NULL);
		newstring[0] = '\0';
	}
	else
		newstring = ft_createstring(s1, set);
	return (newstring);
}
