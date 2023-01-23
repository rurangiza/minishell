/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:41:53 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 14:53:57 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Converts lowercase alphabet character to uppercase
*/

int	ft_toupper(int c)
{
	unsigned char	ch;

	if (c == -1)
		return (c);
	ch = c;
	if (ch >= 97 && ch <= 122)
		ch -= 32;
	return (ch);
}
