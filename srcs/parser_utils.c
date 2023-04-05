/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:47:28 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 11:52:46 by arurangi         ###   ########.fr       */
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
