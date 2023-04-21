/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:41 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/21 13:53:08 by arurangi         ###   ########.fr       */
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

void	simple_redirect(t_token *token, t_prompt *prompt, int index,
			int cmd_type)
{
	if (index != 0)
		dup2(prompt->stdio[WRITE], STDOUT_FILENO);
	if (cmd_type == _middle)
	{
		if (pipe(prompt->pipends) == NO_REDIR)
			exit_msg();
	}
	if (token[index].infile != NO_REDIR)
		redirect_in(&token[index], prompt);
	else if (cmd_type == _middle)
	{
		if (index == 0)
			prompt->prevpipe = prompt->pipends[READ];
		else if (index > 0)
		{
			dup2(prompt->prevpipe, STDIN_FILENO);
			close(prompt->prevpipe);
			prompt->prevpipe = prompt->pipends[READ];
		}
	}
	else if (cmd_type == _last)
		dup2(prompt->prevpipe, STDIN_FILENO);
	if (token[index].outfile != NO_REDIR)
		redirect_out(&token[index]);
	else if (cmd_type == _middle)
		dup2(prompt->pipends[WRITE], STDOUT_FILENO);
	if (cmd_type == _middle)
		close(prompt->pipends[WRITE]);
}
