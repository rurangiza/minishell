/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:41 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/15 13:35:41 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_in(t_token *token)
{
	if (token->infile == HERE_DOC)
	{
		token->infile = heredoc(token->delimiter, token->heredoc_mode);
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
	else
	{
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
}

void	redirect_out(t_token *token)
{
	dup2(token->outfile, STDOUT_FILENO);
	close(token->outfile);
}
