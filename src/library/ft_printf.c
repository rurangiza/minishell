/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:49:26 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/16 11:30:20 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Prints string to standard output and handles basic format specifiers
*/

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		index;
	int		counter;

	counter = 0;
	va_start(args, str);
	index = 0;
	while (str[index])
	{
		if (str[index] == '%' && str[index + 1])
		{
			ft_putfs(str[index + 1], args, &counter);
			index++;
		}
		else
		{
			ft_putchar(str[index]);
			counter++;
		}
		index++;
	}
	va_end(args);
	return (counter);
}

void	ft_putfs(char ch, va_list args, int *counter)
{
	if (ch == 'c')
			*counter += ft_putchar_mod(va_arg(args, int));
	else if (ch == 's')
		*counter += ft_putstr_mod(va_arg(args, char *));
	else if (ch == 'i' || ch == 'd')
		*counter = ft_putnbr_mod(va_arg(args, int), counter);
	else if (ch == 'u')
		*counter = ft_putnbr_u(va_arg(args, unsigned int), counter);
	else if (ch == '%')
		*counter += ft_putchar_mod('%');
	else if (ch == 'x' || ch == 'X')
		ft_puthex(va_arg(args, unsigned int), ch, counter);
	else if (ch == 'p')
	{
		ft_putstr_mod("0x");
		ft_puthex(va_arg(args, unsigned long), ch, counter);
		*counter += 2;
	}
}
