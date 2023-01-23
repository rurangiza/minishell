/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 09:51:01 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/18 14:06:13 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	error_msg(int return_code, char *message, ...)
{
	va_list	args;
	int		index;

	va_start(args, message);
	index = 0;
	while (message[index])
	{
		if (message[index] == '%')
		{
			if (message[index + 1] && message[index + 1] == 's')
				ft_putstr_fd(va_arg(args, char *), 2);
			else if (message[index + 1] && message[index + 1] == 'd')
				ft_putnbr_fd(va_arg(args, int), 2);
			index++;
		}
		else
			ft_putchar_fd(message[index], 2);
		index++;
	}
	write(2, "\n", 1);
	return (return_code);
}
