/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:54:48 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 12:46:05 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Copies {n} characters from {src} to {dst}
 * Unlike memcpy, memmove take care of overlap...
 * 
 * Returns : pointer to destination {dest}
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	index;

	if (!dest && !src)
		return (NULL);
	if (dest >= src)
	{
		index = n - 1;
		while (index < n)
		{
			((unsigned char *)dest)[index] = ((unsigned char *)src)[index];
			index--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
