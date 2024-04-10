/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:03:49 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/25 18:03:50 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*current;

	if (!(lst || del))
		return ;
	temp = *lst;
	current = *lst;
	while (current)
	{
		temp = temp -> next;
		del(current -> content);
		free(current);
		current = temp;
	}
	*lst = NULL;
}
