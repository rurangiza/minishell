/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:38 by akorompa          #+#    #+#             */
/*   Updated: 2022/10/11 13:48:57 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	int_lenght(int n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	unsigned int	res;
	char			*str;
	unsigned int	len;

	len = int_lenght(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		res = -n;
	}
	else
		res = n;
	if (res == 0)
		str[0] = '0';
	str[len] = '\0';
	while (res != 0)
	{
		str[len - 1] = (res % 10) + 48;
		res = res / 10;
		len--;
	}
	return (str);
}
