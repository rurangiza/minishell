/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:51:07 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 15:36:34 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Locates first occurence of the {needle} in {haystack}
 * while searching not more than {len} characters
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_index;
	size_t	n_index;

	if (needle[0])
	{
		h_index = 0;
		while (((char *)haystack)[h_index] && (h_index < len))
		{
			n_index = 0;
			while (haystack[h_index + n_index] == needle[n_index]
				&& ((h_index + n_index) < len))
			{
				if (needle[n_index + 1] == '\0')
					return ((char *)haystack + h_index);
				n_index++;
			}
			h_index++;
		}
		return (0);
	}
	else
		return ((char *)haystack);
}
