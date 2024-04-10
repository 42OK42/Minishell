/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:44:55 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/24 14:44:57 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	counter;

	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	ptr = malloc((len * sizeof(char)) + 1);
	if (ptr == NULL)
		return (NULL);
	counter = 0;
	while (counter < len)
	{
		ptr[counter] = s[start + counter];
		counter++;
	}
	ptr[counter] = 0;
	return (ptr);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const char *str = "Hello";
    unsigned int start = 7;
    size_t len = 5;

    // Call ft_substr
    char *substring = ft_substr(str, start, len);

    if (substring != NULL)
    {
        printf("Substring: %s\n", substring);
        // Remember to free the allocated memory
        free(substring);
    }
    else
    {
        printf("Failed to allocate memory for the substring.\n");
    }

    return 0;
}
*/
