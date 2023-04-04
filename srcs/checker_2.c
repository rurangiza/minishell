/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:44:23 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/04 15:56:25 by arurangi         ###   ########.fr       */
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