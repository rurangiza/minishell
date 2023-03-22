/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:41 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/21 10:44:30 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_in(t_token *token)
{
	
	if (token->infile == HERE_DOC)
	{
		// printf("Delimiter = '%s'\n", token->delimiter);
		// exit(0);
		token->infile = heredoc(token->delimiter, token->heredoc_mode);
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
	else
	{
		if (token->delimiter != NULL)
			heredoc(token->delimiter, token->heredoc_mode);
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
}

void	redirect_out(t_token *token)
{
	dup2(token->outfile, STDOUT_FILENO);
	close(token->outfile);
}
