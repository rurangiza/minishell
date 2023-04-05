/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:58:55 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/05 14:05:14 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	j;
	int	k;

	j = ft_strlen(str) - 1;
	if ((char)c == '\0')
	{
		k = ft_strlen(str);
		return ((char *)str + k);
	}
	while (j >= 0)
	{
		if (str[j] == (char)c)
			return ((char *)str + j);
		j--;
	}
	return (NULL);
}

// Returns index of the last occurence
int	ft_strrchr_mod(const char *str, int c)
{
	int	length;

	length = ft_strlen(str);
	if ((char)c == '\0')
		return (length);
	length--;
	while (length >= 0)
	{
		if (str[length] == (char)c)
			return (length);
		length--;
	}
	return (-1);
}
