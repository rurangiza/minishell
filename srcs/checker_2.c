/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:44:23 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 13:51:11 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_ending_character(char *buffer, int end)
{
	if (ft_isspace(buffer[end])
		|| buffer[end] == '\''
		|| buffer[end] == '\"'
		|| buffer[end] == '$')
		return (TRUE);
	return (FALSE);
}
