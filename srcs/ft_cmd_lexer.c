/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:05:43 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/04 16:57:53 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_word_len(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && prompt[i] != ' ')
	{
		if (prompt[i] == '\"')
		{
			i++;
			while (prompt[i] && prompt[i] != '\"')
				i++;
		}
		else if (prompt[i] == '\'')
		{
			i++;
			while (prompt[i] && prompt[i] != '\'')
				i++;
		}
		if (!prompt[i])
			break ;
		i++;
	}
	return (i);
}

char	*ft_get_words(char *prompt)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_word_len(prompt);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = prompt[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	cmd_lexer(char *prompt, int *i, int *j)
{
	while (prompt[*i] && prompt[*i] != ' '
		&& prompt[*i] != '\"' && prompt[*i] != '\'')
		(*i)++;
	if (prompt[*i] == '\"')
	{
		(*i)++;
		while (prompt[*i] != '\"' && prompt[*i])
			(*i)++;
	}
	else if (prompt[*i] == '\'')
	{
		(*i)++;
		while (prompt[*i] != '\'' && prompt[*i])
			(*i)++;
	}
	(*j)++;
}

char	**ft_cmd_lexer(char *prompt)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!prompt)
		return (NULL);
	if (count_words(prompt) == -1)
	{
		printf("oui\n");
		return (NULL);
	}
	arr = malloc(sizeof(char *) * (count_words(prompt) + 1));
	if (!arr)
		return (NULL);
	while (prompt[i])
	{
		i = skip_spaces(prompt, i);
		if (prompt[i])
		{
			arr[j] = ft_get_words(prompt + i);
			cmd_lexer(prompt, &i, &j);
		}
		i = skip_spaces(prompt, i);
	}
	arr[j] = 0;
	return (arr);
}
