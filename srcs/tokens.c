/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:54:35 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/27 14:42:43 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_isset(char *set, char c)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int get_nb_token(char *str)
{
	int i;
	int count;
	
	count = 1;
	i = 0;
	if (str[i] && str[1] == '\0')
		return (1);
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (str[i + 1] && !(str[i] == '|' || str[i] == '>' || str[i] == '<'))
			count++;
		i++;
	}
	while(str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while(str[i] && str[i] != '\'') //! added 'str[i]' to prevent SEGFAULT
			i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
		}
		if (str[i] == '|')
		{
			count++;
			if (str[i + 1] == '|')
				i++;
			if (str[i + 1] && str[i + 1] != '|')
				count++;
			i++;
		}
		if (str[i] == '>')
		{
			count++;
			if (str[i + 1] == '>')
				i++;
			if (str[i + 1] && str[i + 1] != '>')
				count++;
		}
		if (str[i] == '<')
		{
			count++;
			if (str[i + 1] == '<')
				i++;
			if (str[i + 1] && str[i + 1] != '<')
				count++;
		}
		if (!str[i])
			break ;
		i++;
	}
	return (count);
}

int len_tokens(char *str)
{
	int i;
	int len;

	len = 0;
	i = 0;
	if (ft_isset("<|>", str[i]))
		len++;
	while (str[i] && !ft_isset("<|>", str[i]))
	{
		if (str[i] == '\'')
		{
			i++;
			len++;
			while(str[i] && str[i] != '\'') //! added 'str[i]' to prevent SEGFAULT
			{
				i++;
				len++;
			}
		}
		if (str[i] == '\"')
		{
			i++;
			len++;
			while (str[i] != '\"')
			{
				i++;
				len++;
			}
		}
		if (!str[i]) //! added to prevent SEGFAULT in loop condition
			break ;
		i++;
		len++;
	}
	return (len);
}

char *get_tokens(char *str, int *j, int *k)
{
	int i;
	int len;
	char *line;

	i = 0;
	len = len_tokens(str);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	if (ft_isset("<|>", str[i]))
	{
		line[i] = str[i];
		if (str[i + 1])
			(*j)++;
		else if (str[i + 1] == '\0')
		{
			(*k)++;
			*j = 0;
		}
	}
	while (str[i] && !ft_isset("<|>", str[i]))
	{
		if (str[i] == '\'')
		{
			line[i] = str[i];
			(*j)++;
			i++;
			while (str[i] && str[i] != '\'') //! added 'str[i]' to prevent SEGFAULT
			{
				line[i] = str[i];
				i++;
				(*j)++;
			}
		}
		if (str[i] == '\"')
		{
			line[i] = str[i];
			(*j)++;
			i++;
			while (str[i] != '\"')
			{
				line[i] = str[i];
				i++;
				(*j)++;
			}
		}
		line[i] = str[i];
		(*j)++;
		i++;
		
		/*
		** Next condition causes errors when:
		** (str[i] == '\0') => SEGFAULT for : echo "c'est"'
		** (str[i] && str[i] == '\0') => echo "$HOME" (stops working)
		*/
		if (str[i] == '\0') //! CHECK THIS OUT
		{
			*j = 0;
			(*k)++;
			break ;
		}
	}
	line[len] = 0;
	return (line);
}

char **token(t_lexer *lexer)
{
	char **tokens;
	int i;
	int k;
	int count;
	int len;
	int j;
	
	i = 0;
	count = 0;
	while (lexer->tmp[i])
	{
		len = get_nb_token(lexer->tmp[i]);
		count += len;
		i++;
	}
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	k = 0;
	j = 0;
	while(k < count)
	{
		tokens[k++] = get_tokens(lexer->tmp[i] + j, &j, &i);
	}
	tokens[k] = 0;
	return (tokens);
}
