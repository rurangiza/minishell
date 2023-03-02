/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:49:57 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/01 13:50:48 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			if (argument[index] == '\\')
			{
				char *seq = check_escape_seq(argument, index);
				if (seq != NULL)
				{
					write(1, &seq, 1);
					free(seq);
					index++;
				}
			}
			else	
				write(1, &argument[index], 1);
			index++;
		}
		while (type == 'a' && ft_isspace(argument[index]) && ft_isspace(argument[index - 1]) && argument[index])
			index++;
	}
	if (option == FALSE)
		write(1, "\n", 1);
}

char	*check_escape_seq(char *argument, int index)
{
	int		pos;
	char	*escape_seq;

	escape_seq = "abfnrtvx0";
	pos = 0;
	while (escape_seq[pos])
	{
		if (escape_seq[pos] == argument[index + 1])
			return (ft_substr(argument, index, 2));
		pos++;
	}
	return (NULL);
}