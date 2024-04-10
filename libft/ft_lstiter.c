/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:04:04 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/25 18:04:06 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	t_list	*current;

	if (!lst)
		return ;
	if (!f)
		return ;
	current = lst;
	while (current)
	{
		(*f)(current -> content);
		current = current -> next;
	}
	return ;
}
