/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:17:06 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/19 15:28:30 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_token *token, t_prompt *prompt, int cmd_type, int index)
{
	if (cmd_type == _single)
		single_child(&token[index], prompt);
	else if (cmd_type == _last)
		last_child(&token[index], prompt);
	else
		middle_child(&token[index], prompt, index);
}

///////////////////////////////////////////////////////////////////////////////

void	single_child(t_token *token, t_prompt *prompt)
{
	if (token->infile != -1)
		redirect_in(token, prompt);
	if (token->outfile != -1)
		redirect_out(token);
	handle_execution_errors(token, prompt);
	execve(token->cmd_path, token->cmd, prompt->envp);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	last_child(t_token *token, t_prompt *prompt)
{
	if (token->infile != -1)
		redirect_in(token, prompt);
	else
	{
		dup2(prompt->prevpipe, STDIN_FILENO);
		close(prompt->prevpipe);
	}
	if (token->outfile != -1)
		redirect_out(token);
	else
		dup2(prompt->stdio[WRITE], STDOUT_FILENO);
	handle_execution_errors(token, prompt);
	execve(token->cmd_path, token->cmd, prompt->envp);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	middle_child(t_token *token, t_prompt *prompt, int index)
{
	close(prompt->pipends[READ]);
	if (token->infile != -1)
		redirect_in(token, prompt);
	else if (index > 0)
	{
		dup2(prompt->prevpipe, STDIN_FILENO);
		close(prompt->prevpipe);
	}
	if (token->outfile != -1)
		redirect_out(token);
	else
		dup2(prompt->pipends[WRITE], STDOUT_FILENO);
	close(prompt->pipends[WRITE]);
	handle_execution_errors(token, prompt);
	execve(token->cmd_path, token->cmd, prompt->envp);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	parent_process(t_token *token, t_prompt *prompt, int cmd_type)
{
	if (cmd_type == _middle)
	{
		close(prompt->pipends[WRITE]);
		close(prompt->prevpipe);
		prompt->prevpipe = prompt->pipends[READ];
		if (is_empty_pipe(prompt->pipends[READ])
			&& ft_strncmp("cat", token->cmd[0], 3) == 0
			&& !token->cmd[1] && token->infile < 0)
			close(prompt->pipends[READ]);
	}
	else if (cmd_type == _last)
	{
		dup2(prompt->stdio[READ], STDOUT_FILENO);
		dup2(prompt->stdio[WRITE], STDOUT_FILENO);
		//close(prompt->pipends[WRITE]);
	}
}
