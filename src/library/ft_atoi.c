/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:49:42 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/10 09:34:06 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Converts a string {str} into an integer
 * 
 * Returns : the integer
*/

#include "libft.h"

long	ft_atoi(const char *str)
{
	int		index;
	long	sum;
	long	sign;

	index = 0;
	while (ft_isspace(str[index]))
		index++;
	sign = 1;
	if (ft_issign(str[index]))
	{
		if (str[index] == '-')
			sign *= -1;
		index++;
	}
	sum = 0;
	while (ft_isdigit(str[index]))
		sum = (sum * 10) + (str[index++] - '0');
	if (str[index] && !ft_isdigit(str[index]))
		return (2147483649);
	return (sum * sign);
}
