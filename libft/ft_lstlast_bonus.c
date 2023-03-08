/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:01:07 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/08 11:37:22 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst != NULL)
	{
		printf("********* Enter\n");
		if (!lst->next)
		{
			printf("######### out\n");
			return (lst);
		}
		printf("---------- here (fn %s, ln %i)\n", __func__, __LINE__);
		lst = lst->next;
	}
	return (lst);
}
