/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:45:54 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/16 11:39:40 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_mod(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_mod(char *str)
{
	int	i;

	if (!str)
	{
		ft_putstr_mod("(null)");
		return (6);
	}
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_mod(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr_mod(int nbr, int *counter)
{
	char	ch;

	if (nbr > 9)
	{
		ft_putnbr_mod((nbr / 10), counter);
		ft_putnbr_mod((nbr % 10), counter);
	}
	else if (nbr == INT_MIN)
	{
		return (ft_putstr_mod("-2147483648") + *counter);
	}
	else if (nbr < 0)
	{
		(*counter)++;
		ft_putchar_mod('-');
		nbr = -nbr;
		ft_putnbr_mod(nbr, counter);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		(*counter)++;
		ch = nbr + '0';
		ft_putchar_mod(ch);
	}
	return (*counter);
}

int	ft_puthex(unsigned long nbr, char format, int *counter)
{
	char	ch;
	char	*base;

	base = "0123456789abcdef";
	if (nbr > 16 - 1)
	{
		ft_puthex(nbr / 16, format, counter);
		ft_puthex(nbr % 16, format, counter);
	}
	else
	{
		(*counter)++;
		ch = base[nbr];
		if (format == 'X' && ft_isalpha(ch))
			ch -= 32;
		ft_putchar(ch);
	}
	return (*counter);
}

int	ft_putnbr_u(unsigned int nbr, int *counter)
{
	char			ch;

	if (nbr > 9)
	{
		ft_putnbr_u((nbr / 10), counter);
		ft_putnbr_u((nbr % 10), counter);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		(*counter)++;
		ch = nbr + '0';
		ft_putchar(ch);
	}
	return (*counter);
}
