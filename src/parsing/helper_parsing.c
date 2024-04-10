/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:20:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/02/29 17:20:28 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_words(char **words, t_data *data)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_printf("word[%i] after quote_bulshit with quote \
			status [%i]: %s\n", i, data->quote_flag[i], words[i]);
		i++;
	}
}
