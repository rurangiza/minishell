/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:41:33 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/04 17:07:36 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words_2(char *prompt, int *i, int *count)
{
	while (prompt[*i] && prompt[*i] != ' '
		&& prompt[*i] != '\"' && prompt[*i] != '\'')
		(*i)++;
	if (prompt[*i] == '\"')
	{
		*i = skip_quote_count(prompt, *i, prompt[*i]);
		if (*i == -1)
			return (-1);
	}
	else if (prompt[*i] == '\'')
	{
		*i = skip_quote_count(prompt, *i, prompt[*i]);
		if (*i == -1)
			return (-1);
	}
	(*count)++;
	return (0);
}

int	count_words(char *prompt)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!prompt)
		return (0);
	while (prompt[i])
	{
		i = skip_spaces(prompt, i);
		if (prompt[i])
		{
			if (count_words_2(prompt, &i, &count) == -1)
				return (-1);
		}
		i = skip_spaces(prompt, i);
	}
	return (count);
}
