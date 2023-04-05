/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:47:28 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 13:42:18 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sep(char *sep, char c)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	check_heredoc_mod(char *str, t_token *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			cmd->heredoc_mode = FALSE;
			break ;
		}
		else
			cmd->heredoc_mode = TRUE;
		i++;
	}
}

int	get_size_delimiter(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_sep("\'\"", str[i]))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*delete_quotes_2(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*token;

	len = get_size(str, c);
	token = malloc(sizeof (char) * (len + 1));
	if (!token)
		return (NULL);
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
	return (token);
}

char	*get_delimiter(char *str)
{
	int		i;
	char	*delimiter;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			delimiter = delete_quotes_2(str, '\'');
			return (delimiter);
		}
		else if (str[i] == '\"')
		{
			delimiter = delete_quotes_2(str, '\"');
			return (delimiter);
		}
		i++;
	}
	return (str);
}
