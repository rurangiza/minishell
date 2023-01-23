/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:48:39 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 11:36:21 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Erases the data in the {n} bytes of the memory
 * starting at the location pointed to by {s}, 
 * by writing zeros (bytes containing '\0') to that area
 * 
 * Returns : nothing
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (n)
	{
		i = 0;
		while (i < n)
			((char *)s)[i++] = 0;
	}
}
