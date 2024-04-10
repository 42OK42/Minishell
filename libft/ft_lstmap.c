/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:04:11 by bschmidt          #+#    #+#             */
/*   Updated: 2023/06/25 18:04:12 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*prev_node;

	new_list = NULL;
	new_node = NULL;
	prev_node = NULL;
	while (lst != NULL)
	{
		new_node = malloc(sizeof(t_list));
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node -> content = f(lst -> content);
		new_node->next = NULL;
		if (prev_node != NULL)
			prev_node->next = new_node;
		else
			new_list = new_node;
		prev_node = new_node;
		lst = lst->next;
	}
	return (new_list);
}
