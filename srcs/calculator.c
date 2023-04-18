/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:24:20 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/17 15:55:55 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tablen(char	**tab)
{
	int	len;

	len = 0;
	if (tab)
	{
		while (tab[len])
			len++;
	}
	return (len);
}

int	get_cmd_len(char **tokens, int i)
{
	int	len;

	len = 0;
	while (tokens[i]
		&& not_real(tokens[i], '|')
		&& not_real(tokens[i], '>')
		&& not_real(tokens[i], '<'))
	{
		len++;
		i++;
	}
	return (len);
}
