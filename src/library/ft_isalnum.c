/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:03:38 by arurangi          #+#    #+#             */
/*   Updated: 2022/10/21 11:46:22 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * checks whether {c} is an alphanumeric character or not
 * (alphabet or number) 
 * 
 * Returns : (1) = yes, (0) = no
*/

int	ft_isalnum(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
		return (1);
	if ((c >= 48) && (c <= 57))
		return (1);
	return (0);
}
