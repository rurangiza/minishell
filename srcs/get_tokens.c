/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:26:19 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/05 13:25:55 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	found_set(char *str, int i, int *j, int *k)
{
	if (str[i + 1])
		(*j)++;
	else if (str[i + 1] == '\0')
	{
		(*k)++;
		*j = 0;
	}
}

char	*only_token(char c)
{
	char	*line;
	int		i;

	i = 0;
	line = malloc(sizeof(char) * 2);
	line[i] = c;
	line[1] = 0;
	return (line);
}

int	find_end(char *str, int j)
{
	int	end;

	end = j;
	while (str[j] && !ft_isset("<|>", str[j]))
	{
		if (str[j] == '\'')
		{
			end = skip_quote(str, j, '\'');
			j = skip_quote(str, j, '\'');
		}
		if (str[j] == '\"')
		{
			end = skip_quote(str, j, '\"');
			j = skip_quote(str, j, '\"');
		}
		end++;
		j++;
		if (str[j] == '\0')
			break ;
	}
	return (end);
}

char	*get_tokens(char *str, int *j, int *k)
{
	char	*line;
	int		i;
	int		end;

	i = 0;
	end = *j;
	if (str[i] && ft_isset("<|>", str[i]))
	{
		line = only_token(str[i]);
		found_set(str, i, j, k);
		return (line);
	}
	end = find_end(str, i);
	line = ft_substr(str, i, end);
	*j = end;
	if (str[end] == '\0')
	{
		*j = 0;
		(*k)++;
	}
	return (line);
}
