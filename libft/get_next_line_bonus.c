/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:27:11 by bschmidt          #+#    #+#             */
/*   Updated: 2023/08/25 12:27:12 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_free(char *text, char *buffer)
{
	char	*output;

	output = ft_strjoin(text, buffer);
	free(text);
	text = NULL;
	return (output);
}

char	*read_filenl(int fd, char *text)
{
	char	*buffer;
	int		read_bytes;

	if (!text)
		text = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(text);
			text = NULL;
			return (NULL);
		}
		buffer[read_bytes] = 0;
		text = ft_free(text, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (text);
}

char	*give_first_line(char *text)
{
	int		i;
	char	*line;

	i = 0;
	if (!text[i])
		return (NULL);
	while (text[i] != 0 && text[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (text[i] != 0 && text[i] != '\n')
	{
		line[i] = text[i];
		i++;
	}
	if (text[i] != 0 && text[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*next_line(char *text)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (text[i] != 0 && text[i] != '\n')
		i++;
	if (text[i] == 0)
	{
		free(text);
		text = NULL;
		return (NULL);
	}
	j = i + 1;
	while (text[j] != 0)
		j++;
	rest = malloc(sizeof(char) * j + 1);
	j = i + 1;
	i = 0;
	while (text[j] != 0)
		rest[i++] = text[j++];
	rest[i] = 0;
	free(text);
	text = NULL;
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*text[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text[fd] = read_filenl(fd, text[fd]);
	if (!text[fd])
		return (NULL);
	line = give_first_line(text[fd]);
	text[fd] = next_line(text[fd]);
	return (line);
}
