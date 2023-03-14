/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:11:44 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/08 11:31:22 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	printf("In add_back()\n");
	if (!lst || !new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			printf("------ Adding\n");
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
