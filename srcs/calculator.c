/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:24:20 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 13:41:00 by arurangi         ###   ########.fr       */
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
		&& ft_strncmp(tokens[i], "|", 1)
		&& ft_strncmp(tokens[i], ">", 1)
		&& ft_strncmp(tokens[i], "<", 1))
	{
		len++;
		i++;
	}
	return (len);
}