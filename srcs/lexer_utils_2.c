/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:30:12 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/21 14:38:27 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_token(char *str, char c)
{
	int	i;

	i = 0;
	if (ft_strlen(str) != 3)
		return (0);
	if (str[0] != c && str[2] != c && ft_isset("<|>", str[1]))
		return (0);
	return (1);
}

char	*special_token(char *str)
{
	char	*token;

	token = malloc(sizeof(char) * 3);
	if (!token)
		return (NULL);
	token[0] = str[1];
	token[1] = ' ';
	token[2] = 0;
	return (token);
}

void	delete_quotes_utils(char *str, char *token, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			token[j] = str[i];
			i++;
			j++;
		}
	}
	token[j] = 0;
}
