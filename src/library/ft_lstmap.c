/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:58:51 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/25 13:41:48 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Copie every node of a linked list
 * into a new linked list
 * after modifying the content of each node with a given function
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (0);
	new_lst = 0;
	while (lst)
	{
		tmp = malloc(sizeof(t_list));
		if (!tmp)
			ft_lstclear(&new_lst, del);
		else
		{
			tmp->content = f(lst->content);
			tmp->next = NULL;
			ft_lstadd_back(&new_lst, tmp);
		}
		lst = lst->next;
	}
	return (new_lst);
}
