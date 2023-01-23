/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:01:06 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/05 11:01:06 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Concatenates {dstsize} of {src} to {dest}
 * 
 * Returns : total length of the string you tried to create
*/

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	src_index;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dest)
		dest_len = ft_strlen(dest);
	src_index = 0;
	if (dstsize)
	{
		while (src[src_index] && ((dest_len + src_index) < (dstsize - 1)))
		{
			dest[dest_len + src_index] = src[src_index];
			src_index++;
		}
		dest[dest_len + src_index] = '\0';
	}
	if (dstsize > dest_len)
		return (dest_len + src_len);
	else
		return (dstsize + src_len);
}
