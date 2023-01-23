/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:45:04 by akorompa          #+#    #+#             */
/*   Updated: 2022/10/05 09:06:59 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int n)
{
	int	i;
	int	j;

	i = 0;
	if ((char)n == '\0')
	{
		j = ft_strlen(str);
		return ((char *)str + j);
	}
	while (str[i] != '\0')
	{
		if (str[i] == (char)n)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
