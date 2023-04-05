/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:41:37 by Arsene            #+#    #+#             */
/*   Updated: 2023/04/05 14:05:34 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Check whether ch is a space or not
*/

#include "libft.h"

int	ft_isspace(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}
