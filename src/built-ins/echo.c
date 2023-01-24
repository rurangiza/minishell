/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:20:13 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/24 15:42:01 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 what the -n option does?
*/

#include "../../includes/minishell.h"

void	echo(int option, char *argument)
{
	int		index;
	char	type;

	type = 'a';
	index = 0;
	while (ft_isspace(argument[index]))
		index++;
	if (argument[index] == '"')
		type = 'b';
	while (argument[index] && argument[index] != '|')
	{
		if (argument[index] == '"')
			index++;
		else
		{
			write(1, &argument[index], 1);
			index++;	
		}
		while (type == 'a' && ft_isspace(argument[index]) && ft_isspace(argument[index - 1]) && argument[index])
			index++;
	}
	if (option == FALSE)
		write(1, "\n", 1);
}
