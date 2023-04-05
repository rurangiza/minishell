/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:54:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 12:01:39 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_pipe_nb(t_lexer *lexer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!ft_strncmp(lexer->tokens[i], "|", 1))
		return (-1);
	while (lexer->tokens[i])
	{
		if (!ft_strncmp(lexer->tokens[i], "|", 1))
		{
			if (!ft_strncmp(lexer->tokens[i + 1], "|", 1)
				&& lexer->tokens[i + 1])
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

int	get_outfile_apmod(char *str)
{
	int	outfile;

	if (!str)
		return (-2);
	outfile = open(str, O_APPEND | O_RDWR | O_CREAT, 0644);
	if (outfile < 0)
		return (-1);
	return (outfile);
}

int	get_outfile(char *str)
{
	int	outfile;

	outfile = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		return (-1);
	return (outfile);
}

int	get_infile(char *str)
{
	int	infile;

	infile = open(str, O_RDONLY);
	if (infile < 0)
		return (-1);
	return (infile);
}