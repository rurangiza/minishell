/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:41:27 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/04 18:04:46 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_spaces(char *prompt, int i)
{
	while (prompt[i] && prompt[i] == ' ')
		i++;
	return (i);
}

int	skip_red(char **tokens, int i)
{
	i++;
	if (tokens[i] && tokens[i + 1] && tokens[i][0] == '<')
		i += 2;
	return (i);
}

int	skip_not_spaces(char *prompt, int i)
{
	while (prompt[i] && prompt[i] != ' ')
		i++;
	return (i);
}

int	skip_quote(char *prompt, int i, char quote)
{
	i++;
	while (prompt[i] && prompt[i] != quote)
		i++;
	if (prompt[i] == '\0')
		return (-1);
	return (i);
}

int	skip_quote_count(char *prompt, int i, char quote)
{
	i++;
	while (prompt[i])
	{
		if (prompt[i] == quote)
			break ;
		i++;
	}
	if (prompt[i] == '\0')
		return (-1);
	return (i);
}
