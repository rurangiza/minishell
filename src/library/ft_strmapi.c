/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:59:19 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 14:43:30 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Applies the function {f} to each character of the string {s}
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		s_length;
	char	*ptr;
	int		s_index;

	if (!s || !f)
		return (NULL);
	s_length = ft_strlen(s);
	ptr = malloc(sizeof(char) * (s_length + 1));
	if (!ptr)
		return (NULL);
	s_index = 0;
	while (s[s_index])
	{
		ptr[s_index] = f(s_index, s[s_index]);
		s_index++;
	}
	ptr[s_index] = '\0';
	return (ptr);
}
