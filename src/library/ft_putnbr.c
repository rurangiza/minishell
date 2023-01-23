/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:02:49 by Arsene            #+#    #+#             */
/*   Updated: 2022/12/15 10:53:52 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr)
{
	char	ch;

	if (nbr > 9)
	{
		ft_putnbr((nbr / 10));
		ft_putnbr((nbr % 10));
	}
	else if (nbr == INT_MIN)
	{
		ft_putstr("-2147483648");
	}
	else if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
		ft_putnbr(nbr);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		ch = nbr + '0';
		ft_putchar(ch);
	}
}
