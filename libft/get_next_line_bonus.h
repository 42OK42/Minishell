/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:31:39 by bschmidt          #+#    #+#             */
/*   Updated: 2023/08/25 15:05:25 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# define BUFFER_SIZE 100

char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_next(char *text);
char	*get_next_line(int fd);
char	*ft_line(char *text);
char	*ft_free(char *text, char *buffer);
char	*read_filenl(int fd, char *text);
void	ft_bzero(void *s, size_t n);
int		ft_nlstrlen(const char *str);

#endif // GET_NEXT_LINE_BONUS_H
