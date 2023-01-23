/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:05:32 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 11:58:29 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Converts an integer to a string (ASCII values)
 *
 * Returns : the string representing the integer or NULL if allocation fails
*/

#include "libft.h"

static int	find_len(int nbr);

char	*ft_itoa(int nbr)
{
	unsigned int	nbr_len;
	char			*str;
	unsigned int	u_nbr;

	nbr_len = find_len(nbr);
	str = malloc(sizeof(char) * (nbr_len + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		u_nbr = -nbr;
	}
	else
		u_nbr = nbr;
	if (nbr == 0)
		str[0] = '0';
	str[nbr_len] = '\0';
	while (u_nbr != 0)
	{
		str[nbr_len - 1] = (u_nbr % 10) + '0';
		u_nbr = u_nbr / 10;
		nbr_len--;
	}
	return (str);
}

static int	find_len(int nbr)
{
	int	counter;

	counter = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		counter++;
	while (nbr != 0)
	{
		counter++;
		nbr = nbr / 10;
	}	
	return (counter);
}
