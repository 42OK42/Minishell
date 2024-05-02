/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:23:38 by bschmidt          #+#    #+#             */
/*   Updated: 2024/04/24 21:30:03 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	data->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
	data->env[i] = NULL;
}

void	*malloc1(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_perror("Memory allocation failed.\n");
		exit (1);
	}
	return (ptr);
}

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	ft_printf("ARRAY:\n");
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
	return ;
}

char	**convert_str_to_array(char *str)
{
	char	**array;

	array = malloc(sizeof(char *) * 2);
	array[0] = str;
	array[1] = NULL;
	return (array);
}
