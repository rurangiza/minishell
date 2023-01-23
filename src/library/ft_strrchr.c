/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:17:40 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 14:48:35 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Locate the last occurence of {c} in {s}
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;
	int		save_pos;

	save_pos = -1;
	ch = c;
	i = 0;
	if (ch == '\0')
	{
		while (s[i])
			i++;
		return ((char *)s + i);
	}
	while (s[i])
	{
		if (s[i] == ch)
			save_pos = i;
		i++;
	}
	if (save_pos >= 0)
		return ((char *)s + save_pos);
	else
		return (NULL);
}
