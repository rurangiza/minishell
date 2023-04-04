/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:54:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/04 16:05:10 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quotes_count(char *prompt, int *i, int *count, char quote)
{
	(*count)++;
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
		(*i)++;
	if (prompt[*i] && prompt[*i] == quote)
		(*count)++;
}

int	check_quotes(char *prompt)
{
	int	i;
	int	singlecount;
	int	doublecount;

	i = 0;
	singlecount = 0;
	doublecount = 0;
	while (prompt[i])
	{
		if (prompt[i] && prompt[i] == '\'')
			quotes_count(prompt, &i, &singlecount, prompt[i]);
		if (prompt[i] && prompt[i] == '\"')
			quotes_count(prompt, &i, &doublecount, prompt[i]);
		if (!prompt[i])
			break ;
		i++;
	}
	if (((doublecount % 2) != 0) || ((singlecount % 2) != 0))
		return (-1);
	else
		return (0);
	return (0);
}
