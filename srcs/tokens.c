/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:54:35 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/17 16:12:57 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isset(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	len_tokens(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (ft_isset("<|>", str[i]))
		len++;
	while (str[i] && !ft_isset("<|>", str[i]))
	{
		if (str[i] == '\'')
			i = len_utils(str, &len, i, str[i]);
		if (str[i] == '\"')
			i = len_utils(str, &len, i, str[i]);
		if (!str[i])
			break ;
		i++;
		len++;
	}
	return (len);
}

// char *get_tokens(char *str, int *j, int *k)
// {
// 	int i;
// 	int len;
// 	char *line;

// 	i = 0;
// 	len = len_tokens(str);
// 	line = malloc(sizeof(char) * (len + 1));
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	if (ft_isset("<|>", str[i]))
// 	{
// 		line[i] = str[i];
// 		found_set(str, i, j, k);
// 	}
// 	while (str[i] && !ft_isset("<|>", str[i]))
// 	{
// 		if (str[i] == '\'')
// 		{
// 			line[i] = str[i];
// 			(*j)++;
// 			i++;
// 			while (str[i] && str[i] != '\'')
// 			{
// 				line[i] = str[i];
// 				i++;
// 				(*j)++;
// 			}
// 		}
// 		if (str[i] == '\"')
// 		{
// 			line[i] = str[i];
// 			(*j)++;
// 			i++;
// 			while (str[i] != '\"')
// 			{
// 				line[i] = str[i];
// 				i++;
// 				(*j)++;
// 			}
// 		}
// 		line[i] = str[i];
// 		(*j)++;
// 		i++;
// 		if (str[i] == '\0')
// 		{
// 			*j = 0;
// 			(*k)++;
// 			break ;
// 		}
// 	}
// 	line[len] = 0;
// 	return (line);
// }

char	**token(t_lexer *lexer)
{
	char	**tokens;
	t_utils	utils;
	int		i;
	int		j;

	i = 0;
	utils.count = 0;
	while (lexer->tmp[i])
	{
		utils.len = get_nb_token(lexer->tmp[i]);
		utils.count += utils.len;
		i++;
	}
	tokens = malloc(sizeof(char *) * (utils.count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	utils.k = 0;
	j = 0;
	while (utils.k < utils.count)
	{
		tokens[utils.k++] = get_tokens(lexer->tmp[i] + j, &j, &i);
	}
	tokens[utils.k] = 0;
	return (tokens);
}
