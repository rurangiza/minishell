/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:44:31 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 12:59:39 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Duplicate a string (Deep copy)
 *
 * Returns : the deep copy
*/

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*deep_copy;
	int		s_len;
	int		s_index;

	s_len = ft_strlen(str);
	deep_copy = (char *) malloc(sizeof(char) * (s_len + 1));
	if (!deep_copy)
		return (NULL);
	s_index = 0;
	while (str[s_index])
	{
		deep_copy[s_index] = str[s_index];
		s_index++;
	}
	deep_copy[s_index] = '\0';
	return (deep_copy);
}
