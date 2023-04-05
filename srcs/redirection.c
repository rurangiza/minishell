/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:41 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 17:06:30 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_in(t_token *token, t_prompt *prompt)
{
	if (token->infile == HERE_DOC)
	{
		signal(SIGINT, handle_inheredoc_signals);
		token->infile = heredoc(token->delimiter, token->heredoc_mode, prompt);
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
	else
	{
		if (token->delimiter != NULL)
			heredoc(token->delimiter, token->heredoc_mode, prompt);
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
}

void	redirect_out(t_token *token)
{
	dup2(token->outfile, STDOUT_FILENO);
	close(token->outfile);
}

void	simple_redirect(t_token *token, t_prompt *prompt, int index)
{
	if (token[index].infile != -1)
		redirect_in(&token[index], prompt);
	if (token[index].outfile != -1)
		redirect_out(&token[index]);
	if (index > 0)
		close(prompt->prevpipe);
}
