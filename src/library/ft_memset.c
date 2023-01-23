/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:19:37 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 12:48:16 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Copies given character {ch} to the first {nbr} characters
 * of the string {str}
*/

#include "libft.h"

void	*ft_memset(void *str, int ch, size_t nbr)
{
	size_t	i;

	i = 0;
	while (i < nbr)
	{
		((unsigned char *)str)[i] = (unsigned char)ch;
		i++;
	}
	return (str);
}
