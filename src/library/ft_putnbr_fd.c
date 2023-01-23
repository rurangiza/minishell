/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:32:11 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 15:17:53 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Outputs integer {nbr} to the given file descriptor {fd}
*/

#include "libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	char	ch;

	if (nbr > 9)
	{
		ft_putnbr_fd((nbr / 10), fd);
		ft_putnbr_fd((nbr % 10), fd);
	}
	else if (nbr == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
	}
	else if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
		ft_putnbr_fd(nbr, fd);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		ch = nbr + '0';
		ft_putchar_fd(ch, fd);
	}
}
